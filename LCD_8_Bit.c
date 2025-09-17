#include"LCD_8_Bit.h"
#include <xc.h>
void LCD_CMD(char cmd)
{
	RS = 0; //FOR COMMAND REGISTER
	//RW = 0; //For Write Operation
	
	LCD = cmd;
	//For High to LOw Pulse
	EN = 1; //Enable is One
	__delay_ms(5);
	EN = 0; //Enable is 0 
}

void LCD_Data(char Data)
{
	RS = 1; //FOR Data REGISTER
	//RW = 0; //For Write Operation
	LCD = Data;
	//For High to LOw Pulse
	EN = 1; //Enable is One
	__delay_ms(5);
	EN = 0; //Enable is 0 
}

void LCD_Initialize()
{   
    TRISD=0x00; //PORT B as a Output
    TRISC0=0; //RS
    TRISC1=0;//EN
    //TRISC2=0;//EN
	__delay_ms(10);
	LCD_CMD(0X38); // Initialization of 16X2 LCD in 8bit mode
	LCD_CMD(0X0C); // Display On, Cursor Off
	LCD_CMD(0X06); // Auto Increment cursor
	LCD_CMD(0X01); //Clear Display
}
void LCD_String(char *str)
{
	while(*str)
	LCD_Data(*str ++);

}