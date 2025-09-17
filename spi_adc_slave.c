/*
 * File:   spi_adc_slave.c
 * Author: pooja
 *
 * Created on 30 May, 2025, 1:56 PM
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

#include <pic16f877a.h>
#include <xc.h>
#define _XTAL_FREQ 20000000
#include"LCD_8_Bit.h"
#include "ADC_LCD_8Bit.h"

//Forward Declaration for SPI_read
char rxStr[4];
unsigned int x;
unsigned char SPI_Read();
void adc_read_rx();
void adc_String(char *Output, unsigned int length);

void main(void) 
{
    //Direction set
    TRISC5 = 0;     //SDO -O/P
    TRISC4 = 1;     //SDI as input
    TRISC3 = 1;     //CLK as input
    
    LCD_Initialize(); //Initializations of LCD
    ADC_Conf();//Configuartions of ADC
    
    //Configuration for SPI
    SSPSTAT =0X00;
    //SSPCON1 =0X25;
    SSPEN=1; 
    CKP=0; 
    SSPM3=0;
    SSPM2=1;
    SSPM1=0;
    SSPM0=1;
    
    LCD_CMD(0x80); //First Row
    LCD_String("ADC Value Slave");
    while(1)
    {
        adc_read_rx(); 
        //To display value on LCD receive
        LCD_CMD(0XC0);
        LCD_Data(rxStr[0]);
        LCD_Data(rxStr[1]);
        LCD_Data(rxStr[2]);
        LCD_Data(rxStr[3]);
    }
    
    return;
}

unsigned char SPI_Read()
{    
    SSPBUF=0xff;                 /* Put flush data in SSBUF to read from device */
    while(!PIR1bits.SSPIF);      /* wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;
    return(SSPBUF);              /* read data as it is returned from slave to master.
                                     so SSPBUF is ready to receive new data.*/   
}

void adc_read_rx()
{
    unsigned char s;
    s = SPI_Read();
    if(s == ':')
    {
        adc_String(rxStr,4);//passing array base address with length
        x = rxStr[0]*1000+rxStr[1]*100+rxStr[2]*10+rxStr[3];          
    }
}

void adc_String(char *Output, unsigned int length)
{
   unsigned int i;
   for(i=0;i<length;i++)// 4 is a length of transmitting data
   {  
    *(Output+i)=SPI_Read();
   }
}