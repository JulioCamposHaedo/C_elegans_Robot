#ifndef PWM2_H
 #define PWM2_H

 #include <xc.h>
 #include <stdint.h>

 #define PWM2_INITIALIZE_DUTY_VALUE    46

/**
 * \brief Inicializa la interfaz PWM2.
 *
 * \param[in] Ninguno
 *
 * \return Vacío

 */
 void PWM2_Initialize(void);

/**
 * \brief Carga el duty cycle de 16 bits.
 *
 * \param[in] dutyValue- Duty cycle de 16 bits.
 *
 * \return Vacío
   
 */
 void PWM2_LoadDutyValue(uint16_t dutyValue);


 #endif	//PWM2_H
