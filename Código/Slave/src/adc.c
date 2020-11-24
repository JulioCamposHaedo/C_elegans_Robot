#include <xc.h>
#include "adc.h"
#include "device_config.h"

#define ACQ_US_DELAY 5

void ADC_Initialize(void)
{
    
    // ADFM derecha; ADPREF VDD; ADCS FOSC/4; 
    ADCON1 = 0xC0;
    
    // TRIGSEL no_auto_trigger; 
    ADCON2 = 0x00;
    
    // ADRESL 0; 
    ADRESL = 0x00;
    
    // ADRESH 0; 
    ADRESH = 0x00;
    
    // GO_nDONE stop; ADON habilitado; CHS ningun canal seleccionado; 
    ADCON0 = 0x01;
    
}



adc_result_t ADC_GetConversion(adc_channel_t channel)
{
    // Selección canal A/D
    ADCON0bits.CHS = channel;    
    
    // Prender módulo ADC
    ADCON0bits.ADON = 1;

    // Tiempo de delay de adquisición
    __delay_us(ACQ_US_DELAY);

    // Empieza la conversión
    ADCON0bits.GO_nDONE = 1;

    // Esperar a que la conversión termine
    while (ADCON0bits.GO_nDONE)
    {
    }

    // Conversion finalizada, devuelve el resultado
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}
