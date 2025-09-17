#include "ADC_LCD_8Bit.h"


void ADC_Conf()
{
  //ADC Configurations
  ADCON0 = 0X85;
  ADCON1 = 0XC4;   
}

unsigned int ADC_Conversion()
{
      GO_nDONE = 1; //START THE CONVERSION
      while(GO_nDONE == 1);  //Monitor the flag till complete
      adc_read = (ADRESL | (ADRESH <<8));
      
      return adc_read;
}

