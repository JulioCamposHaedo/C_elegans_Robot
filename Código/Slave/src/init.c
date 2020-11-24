#include "init.h"


void SYSTEM_Initialize(void)
{
    I2C_Initialize();
    Datos_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    WDT_Initialize();
    PWM1_Initialize();
    PWM2_Initialize();
    ADC_Initialize();
    TMR2_Initialize();
    TMR1_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS INTOSC; SPLLMULT 4xPLL; SPLLEN deshabilitado; IRCF 2MHz_HF; 
    OSCCON = 0x32;
    // TUN 0; 
    OSCTUNE = 0x00;
    // ACTSRC SOSC; ACTUD habilitado; ACTEN deshabilitado; 
    ACTCON = 0x00;
    // SBOREN deshabilitado; BORFS deshabilitado; 
    BORCON = 0x00;
}

void WDT_Initialize(void)
{
    // WDTPS 1:65536; SWDTEN OFF; 
    WDTCON = 0x16;
}
