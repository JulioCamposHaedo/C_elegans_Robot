
#ifndef TMR1_H
#define TMR1_H

#include <stdbool.h>
#include <stdint.h>
    
/**
 * \brief Routina que inicializa el TMR1.
 *        Debe llamarse antes que cualquier otra rutina de TMR1.
 *        Solo debe llamarse una vez durante la inicialización del sistema.
 *
 * \param[in] Ninguno
 *
 * \return Vacío

 */
void TMR1_Initialize(void);

/**
 * \brief Función que le escribe al registro TMR1.
 *        Debe llamarse luego de la operación que inicializa el TMR1.
 *
 * \param[in] timerVal - Valor que se le escribe al registro TMR1
 *
 * \return readVal Valor actual del registro TMR1.
 */
void TMR1_WriteTimer(uint16_t timerVal);

/**
 * \brief Rutina de serivio de interrupción del Timer.
 *        Esta rutina es llamada por el Interrupt Manager.
 *
 * \param[in] Ninguno
 *
 * \return Vacío
*/
void TMR1_ISR(void);

/**
 * \brief Setea el handler del interruptor del temporizador.
 *
 * \param[in] Ninguno
 *
 * \return Vacío
*/
 void TMR1_SetInterruptHandler(void (* InterruptHandler)(void));

 /**
 * \brief Esta es una función puntero a la función que será llamada durante la ISR.
 *
 * \param[in] Ninguno
 *
 * \return Vacío
*/
extern void (*TMR1_InterruptHandler)(void);

#endif // TMR1_H
