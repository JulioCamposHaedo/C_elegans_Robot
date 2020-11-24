#include <xc.h>
#include "pwm1.h"
#include "i2c_slave.h"

 void PWM1_Initialize(void)
 {
    // PWM1POL active_hi; PWM1OE habilitado; PWM1EN habilitado; 
    PWM1CON = 0xC0;   

    // PWM1DCH 11; 
    PWM1DCH = 0x0B;   

    // PWM1DCL 2; 
    PWM1DCL = 0x80;   

 }

 void PWM1_LoadDutyValue(uint16_t dutyValue)
 {
     // Escribe a los 8 MSBs del duty cycle del PWM en el registro PWMDCH 
     PWM1DCH = (dutyValue & 0x03FC)>>2;
     
     // Escribe a los 2 LSBs del duty cycle del PWM en el registro PWMDCL 
     PWM1DCL = (dutyValue & 0x0003)<<6;
 }
