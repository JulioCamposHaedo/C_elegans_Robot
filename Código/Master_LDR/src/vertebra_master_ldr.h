#ifndef VERTEBRA_MASTER_LDR_H
#define	VERTEBRA_MASTER_LDR_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define NUMERO_ESCLAVOS 2 //Cantidad de modulos de accion
#define PWM_REG 15 // Direccion de memoria de PWM
#define DAT1_REG 1 // Direccion de memoria de valor 1 de los sensores
#define DAT2_REG 2 // Direccion de memoria de valor 2 de los sensores
#define DAT3_REG 3 // Direccion de memoria de valor 3 de los sensores
#define DAT4_REG 4 // Direccion de memoria de valor 4 de los sensores

/**
 * Valor que se le escribe al esclavo representando el duty cycle
 * Rango de los servomotores: 0°-180°
 * Rango del ciclo: 15-75
 * El ciclo se puede calcular como: (ángulo del servomotor/3)+15
 */

uint8_t cicloMin = 15;
uint8_t cicloReposo = 45;
uint8_t cicloMax = 75;

/**
 * \brief Handler de la interrupción del TMR1
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */
void TMR1_Master_InterruptHandler(void);

/**
 * \brief Obtiene el estado del flag del handler de interrupción de TMR1
 *
 * \param[in] Ninguno
 *
 * \return Estado del flag
 */
uint8_t Get_Master_TMR1_flag(void);

/**
 * \brief Resetea el estado del flag del handler de interrupción de TMR1
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */
void Clear_Master_TMR1_flag(void);

/**
 * \brief Lee los sensores del esclavo seleccionado
 *
 * \param[in] Esclavo al cual se le desea leer los sensores
 *
 * \return Vacío
 */
void Read_Slave_Sensors(uint8_t esclavo);

/**
 * \brief Lee los sensores de todos los esclavos
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */
void Read_All_Slave_Sensors(void);

#endif	/* VERTEBRA_MASTER_LDR_H */

