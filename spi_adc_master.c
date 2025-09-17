/*
 * File:   spi_adc_master.c
 * Author: pooja
 *
 * Created on 30 May, 2025, 1:26 PM
 */


// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include <pic16f877a.h>
#include"LCD_8_Bit.h"
#include "ADC_LCD_8Bit.h"
#define _XTAL_FREQ 20000000

void Data_Transmit(unsigned char Tx_Data);

void main(void) 
{
    TRISC5 = 0;     //SDO - O/P
    TRISC4 = 1;     //SDI - I/P
    TRISC3 = 0;     //CLK - O/P
    
    LCD_Initialize(); //Initializations of LCD
    ADC_Conf();//Configuartions of ADC
    
    //Configurations of SPI
    SSPSTAT =0X80;
    //WCOL SSPOV 
    SSPEN=1; 
    CKP=0; 
    SSPM3=0;
    SSPM2=0;
    SSPM1=1;
    SSPM0=0;
    
    LCD_CMD(0x80); //First Row
    LCD_String("ADC Value Master");
    while(1)
    {
        unsigned int adc_value=0;
        adc_value=ADC_Conversion(); //get value of adc read
        
        LCD_CMD(0xC0); //Second Row
        LCD_Data((adc_value/1000)+'0'); //D4 
        LCD_Data(((adc_value/100)%10)+'0');//d3
        LCD_Data(((adc_value/10)%10)+'0');//D2
        LCD_Data((adc_value%10)+'0');//D1
        
        Data_Transmit(':');
        Data_Transmit((adc_value/1000)+'0');
        Data_Transmit(((adc_value/100)%10)+'0');
        Data_Transmit(((adc_value/10)%10)+'0');
        Data_Transmit((adc_value%10)+'0');
        
    }
    
    return;
}

void Data_Transmit(unsigned char Tx_Data)
{
	SSPBUF = Tx_Data;
	while(!SSPIF);			//when SSPIF==1 condition false
	SSPIF=0;
}