 #ifndef VERTEBRA_H
#define	VERTEBRA_H

#include <xc.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"

#define NUMERO_ESCLAVOS 2 //Cantidad de modulos de accion
#define PWM_REG 15 // Direccion de memoria de PWM

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
 * \brief Setea el valor del duty cycle que le envia al esclavo seleccionado
 *
 * \param[in] slave- Esclavo seleccionado;ciclo- valor que se le envia al esclavo correspondiente a un duty cycle
 *
 * \return Vacío
 */
void SetServo(i2c_address_t slave, uint8_t ciclo);

/**
 * \brief Secuencia de movimientos preestablecidos mostrando el rango de rotacion de un módulo seleccionado
 *
 * \param[in] esclavo- esclavo seleccionado para rotar
 *
 * \return Vacío
 */
void Rotar_Slave(uint8_t esclavo);

/**
 * \brief Secuencia de movimientos preestablecidos para todos los módulos de acción
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */
void Rotar_All_Slaves(void);
#endif // VERTEBRA_H

