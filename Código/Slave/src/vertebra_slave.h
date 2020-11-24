#ifndef VERTEBRA_H
#define	VERTEBRA_H

#include <xc.h>   
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define PWM_REG 15// Direccion de memoria de PWM
#define CYCLE_SUM_MAX 90 //La suma entre el ciclo minimo (15) y maximo (75) con el que se carga la función que gira los servos

//Estructura de la memoria del esclavo
typedef struct
{
    uint8_t dato1;
    uint8_t dato2;
    uint8_t dato3;
    uint8_t dato4;
    uint8_t ciclo;     
}datos_t;


/**
 * \brief Inicializa los datos en la estructura.
 *
 * \param[in] Ninguno
 *
 * \return Vacío

 */
void Datos_Initialize(void);

/**
 * \brief Handler de la interrupción del TMR1
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */
void TMR1_Slave_InterruptHandler(void);

/**
 * \brief Obtiene el estado del flag del handler de interrupción de TMR1
 *
 * \param[in] Ninguno
 *
 * \return Estado del flag
 */
uint8_t Get_TMR1_flag(void);

/**
 * \brief Resetea el estado del flag del handler de interrupción de TMR1
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */
void Clear_TMR1_flag(void);

/**
 * \brief Handler de la interrupción del I2C y almacena el registro de escritura
 *
 * \param[in] reg- registro al cual el master quiere escribir
 *
 * \return Vacío
 */
void I2C_reg_Slave_InterruptHandler(uint8_t reg);

/**
 * \brief Obtiene el estado del flag del handler de interrupción de I2C
 *
 * \param[in] Ninguno
 *
 * \return Estado del flag
 */
uint8_t Get_I2C_reg_flag(void);

/**
 * \brief Obtiene el valor del registro del handler de interrupción de I2C
 *
 * \param[in] Ninguno
 *
 * \return Estado del flag
 */
uint8_t Get_I2C_reg(void);

/**
 * \brief Resetea el estado del flag del handler de interrupción de I2C
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */
void Clear_I2C_reg_flag(void);

/**
 * \brief Setea flag cuando se escribe el PWM_REG
 *
 * \param[in] reg- registro al cual el master quiere escribir
 *
 * \return Vacío
 */
void I2C_data_slave_flag(void);

/**
 * \brief Obtiene el estado del flag cuando se escribe el PWM_REG
 *
 * \param[in] Ninguno
 *
 * \return Estado del flag
 */
uint8_t Get_I2C_data_flag(void);

/**
 * \brief Resetea el estado del flag cuando se escribe el PWM_REG
 *
 * \param[in] Ninguno
 *
 * \return Estado del flag
 */
void Clear_I2C_data_flag(void);

/**
 * \brief Rutina de lectura y escritura en la interrupción de I2C
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */
void I2C_Read_Write(uint8_t data);

/**
 * \brief Rutina de lectura de los sensores
 *
 * \param[in] Ninguno
 *
 * \return Vacío
 */

void Read_Ldr(void);

#endif // VERTEBRA_H

