# LCD

## LCD Driver on PORT B pins (4-5-6-7) - Atmega32 -

## APIs
### void LCD_init();
### void LCD_Write_CMD (unsigned char CMD);
### void LCD_Write_Data (unsigned char Data);
### void LCD_EN();
### void Toggle_Curcor_Pos();
### void LCD_GoTo(unsigned char posX,unsigned char posY);
### void LCD_Write_String( char *string);
### void LCD_Send_String_Row_Column(char Row,char Column,char *String);
### void LCD_Int_2_String(int x , char* string);
