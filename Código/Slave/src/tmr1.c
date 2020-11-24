#include <xc.h>
#include "tmr1.h"
#include "vertebra_slave.h"

volatile uint16_t timer1ReloadVal;
void (*TMR1_InterruptHandler)(void);

void TMR1_Initialize(void)
{
    //T1GSS T1G_pin; TMR1GE deshabilitado; T1GTM deshabilitado; T1GPOL low; T1GGO_nDONE done; T1GSPM deshabilitado; 
    T1GCON = 0x00;

    //TMR1H 231; 
    TMR1H = 0xE7;

    //TMR1L 150; 
    TMR1L = 0x96;

    // Resetea el IF flag antes de habilitar la interrupción.
    PIR1bits.TMR1IF = 0;

    // Carga el valor TMR a la variable de reload
    timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    // Habilita la interrupcion TMR1.
    PIE1bits.TMR1IE = 1;

    // Setea el handler de interrupción.
    TMR1_SetInterruptHandler(TMR1_Slave_InterruptHandler);

    // T1CKPS 1:8; T1OSCEN deshabilitado; nT1SYNC synchronize; TMR1CS FOSC/4; TMR1ON habilitado; 
    T1CON = 0x31;
}


void TMR1_WriteTimer(uint16_t timerVal)
{
    if (T1CONbits.nT1SYNC == 1)
    {
        // Frena el timer escribiendo al bit TMRxON
        T1CONbits.TMR1ON = 0;

        // Escribe al registro de Timer1
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;

        // Empieza el Timer despues de escribir al registro
        T1CONbits.TMR1ON =1;
    }
    else
    {
        // Escribe al registro de Timer1
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;
    }
}

void TMR1_ISR(void)
{

    // Resetea flag de interrupción de TMR1
    PIR1bits.TMR1IF = 0;
    TMR1_WriteTimer(timer1ReloadVal);

    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();
    }
}


void TMR1_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR1_InterruptHandler = InterruptHandler;
}
