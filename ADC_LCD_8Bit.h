#include <xc.h>
#include <pic16f877a.h>
#define _XTAL_FREQ 20000000
#include"LCD_8_Bit.h"


unsigned int adc_read = 0;

void ADC_Conf();
unsigned int ADC_Conversion();