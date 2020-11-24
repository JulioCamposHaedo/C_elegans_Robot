#include "init.h"


void SYSTEM_Initialize(void)
{

    I2C_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    WDT_Initialize();
    TMR1_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS INTOSC; SPLLMULT 4xPLL; SPLLEN disabled; IRCF 2MHz_HF; 
    OSCCON = 0x32;
    // TUN 0; 
    OSCTUNE = 0x00;
    // ACTSRC SOSC; ACTUD enabled; ACTEN disabled; 
    ACTCON = 0x00;
    // SBOREN disabled; BORFS disabled; 
    BORCON = 0x00;
}

void WDT_Initialize(void)
{
    // WDTPS 1:65536; SWDTEN OFF; 
    WDTCON = 0x16;
}

/**
 End of File
*/
