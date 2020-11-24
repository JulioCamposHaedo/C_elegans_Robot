#include "interrupt_manager.h"
#include "init.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // Handler de interrupción
    if(INTCONbits.PEIE == 1)
    {
        if(PIE2bits.BCL1IE == 1 && PIR2bits.BCL1IF == 1)
        {
            MSSP_InterruptHandler();
        } 
        else if(PIE1bits.SSP1IE == 1 && PIR1bits.SSP1IF == 1)
        {
            MSSP_InterruptHandler();
        } 
        else if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
        {
            TMR1_ISR();
        } 
        else
        {

        }
    }      
    else
    {

    }
}
