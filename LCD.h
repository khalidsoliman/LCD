/*
 * LCD.h
 *
 *  Created on: Jan 3, 2018
 *      Author: Khalid
 */

#ifndef LCD_LCD_H_
#define LCD_LCD_H_

void LCD_init();
void LCD_Write_CMD (unsigned char CMD);
void LCD_Write_Data (unsigned char Data);
void LCD_EN();
void Toggle_Curcor_Pos();
void LCD_GoTo(unsigned char posX,unsigned char posY);
void LCD_Write_String( char *string);
void LCD_Send_String_Row_Column(char Row,char Column,char *String);
void LCD_Int_2_String(int x , char* string);


#endif /* LCD_LCD_H_ */
