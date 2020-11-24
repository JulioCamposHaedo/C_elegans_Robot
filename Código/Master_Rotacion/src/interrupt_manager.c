#include "interrupt_manager.h"
#include "init.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // Handler de interrupción
    if(INTCONbits.PEIE == 1)
    {
        if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
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
