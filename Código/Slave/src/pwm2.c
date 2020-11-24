#include <xc.h>
#include "pwm2.h"
#include "i2c_slave.h"

 void PWM2_Initialize(void)
 {
    // PWM2POL active_hi; PWM2OE habilitado; PWM2EN habilitado; 
    PWM2CON = 0xC0;   

    // PWM2DCH 11; 
    PWM2DCH = 0x0B;   

    // PWM2DCL 2; 
    PWM2DCL = 0x80;   

 }

 void PWM2_LoadDutyValue(uint16_t dutyValue)
 {
     // Escribe a los 8 MSBs del duty cycle del PWM en el registro PWMDCH 
     PWM2DCH = (dutyValue & 0x03FC)>>2;
     
     // Escribe a los 2 LSBs del duty cycle del PWM en el registro PWMDCL 
     PWM2DCL = (dutyValue & 0x0003)<<6;
 }
