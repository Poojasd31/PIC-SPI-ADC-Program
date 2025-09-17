#include <xc.h>
#include <pic16f877a.h>
#define _XTAL_FREQ 20000000
#define RS RC0
#define EN RC1
//#define EN RC2
#define LCD PORTD
//FORWARD declaration
void LCD_Initialize();
void LCD_CMD(char);
void LCD_Data(char);
void LCD_String(char *);