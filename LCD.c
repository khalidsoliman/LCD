/*
 * LCD.c
 *
 *  Created on: Jan 3, 2018
 *      Author: Khalid
 */
#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define set_bit(reg,pin) reg|=(1<<pin)
#define clear_bit(reg,pin) reg&=~(1<<pin)

static int toggle_counter = 0;
static int curcor_counter = 0;

void LCD_EN()
{
	set_bit(PORTC,7);
	_delay_us(5);
	clear_bit(PORTC,7);
}
void LCD_init()
{
	// Make PORT output
	DDRB|=0xf0;
	// Init PORT
	PORTB&=~(0xf0);
	////////////////////////////////////////
	// Make RS Output
	set_bit(DDRC,PC6);
	 // Make EN Output
	set_bit(DDRC,PC7);

	LCD_Write_CMD(0x02); // Return Home
	LCD_Write_CMD(0x28); // 4 bit mode 5*8 dispaly  2 line
	_delay_ms(1);
	LCD_Write_CMD(0x01); // Clear All Display Data
	LCD_Write_CMD(0x0E); // Display on-Cursor on-Blink off
	LCD_Write_CMD(0x06); // after every character cursor will move to right
}
void LCD_Write_CMD(unsigned char CMD)
{
	clear_bit(PORTC,6);
	PORTB&=0x0F;
	PORTB |=(CMD&0xF0) ;
	LCD_EN();
	PORTB&=0x0F;
	PORTB |=((CMD<<4)&0xF0);
	LCD_EN();
	if (CMD==0x01)	curcor_counter = 0;
	_delay_ms(2);
}
void Toggle_Curcor_Pos()
{
	curcor_counter++;
	if(curcor_counter==16)
	{
		LCD_Write_CMD(0xC0);
		curcor_counter=0;
		toggle_counter++;
	}
	if(toggle_counter==2)
	{
		LCD_Write_CMD(0x80);
		toggle_counter=0;
	}
}

void LCD_Write_Data (unsigned char Data)
{
	set_bit(PORTC,6);
	PORTB&=0x0F;
	PORTB |=(Data&0xF0) ;
	LCD_EN();
	PORTB&=0x0F;
	PORTB |=((Data<<4)&0xF0);
	LCD_EN();
	Toggle_Curcor_Pos();
	_delay_ms(1);
}

void LCD_Write_String(char *string)
{
	while(*string!='\0')
	{
		LCD_Write_Data(*string);
		string ++;
	}
	curcor_counter=0;
	toggle_counter=0;
}
void LCD_GoTo(unsigned char posX,unsigned char posY)
{
	unsigned char curcor_pos[] = {0x80,0xC0};
	LCD_Write_CMD(curcor_pos[posX-1]+posY-1);
}
void LCD_Send_String_Row_Column(char Row,char Column,char *String)
{
	LCD_GoTo(Row,Column);
	LCD_Write_String(String);
}
void LCD_Int_2_String(int x , char* string)
{
	sprintf(string, "%d", x);
}
