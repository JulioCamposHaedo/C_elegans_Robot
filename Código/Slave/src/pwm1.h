#ifndef PWM1_H
 #define PWM1_H

 #include <xc.h>
 #include <stdint.h>


 #define PWM1_INITIALIZE_DUTY_VALUE    46


/**
 * \brief Inicializa la interfaz PWM1.
 *
 * \param[in] Ninguno
 *
 * \return Vacío

 */
 void PWM1_Initialize(void);
 
/**
 * \brief Carga el duty cycle de 16 bits.
 *
 * \param[in] dutyValue- Duty cycle de 16 bits.
 *
 * \return Vacío
   
 */

 void PWM1_LoadDutyValue(uint16_t dutyValue);


 #endif	//PWM1_H
