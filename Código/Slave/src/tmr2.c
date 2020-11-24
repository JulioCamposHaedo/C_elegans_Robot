#include <xc.h>
#include "tmr2.h"

void TMR2_Initialize(void)
{
    // PR2 155; 
    PR2 = 0x9B;

    // TMR2 0; 
    TMR2 = 0x00;

    // Resetea el IF flag.
    PIR1bits.TMR2IF = 0;

    // T2CKPS 1:64; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0x07;
}
