#ifndef ADC_H
#define ADC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


//Tamaño del resultado de ujna conversión A/D
typedef uint16_t adc_result_t;

//Definición del canal ADC

typedef enum
{
    LDR_Left =  0x3,
    LDR_Right =  0x6,
    channel_Temp =  0x1D,
    channel_DAC =  0x1E,
    channel_FVR =  0x1F
} adc_channel_t;

/**
 * \brief Inicializa el ADC.
 *        Esta rutina debe llamarse antes de cualquier otra rutina del ADC
 *        A esta rutina se la debería llamar una sola vez durante la inicialización del sistema
 *
 * \param[in] Ninguno
 *
 * \return Vacío

 */
void ADC_Initialize(void);

/**
 * \brief Esta rutina devuelve el valor de la conversión A/D del canal seleccionado.
 *
 * \param[in] channel- Canal donde se desea realizar la conversión A/D.
 *
 * \return Valor de la conversión.

 */
adc_result_t ADC_GetConversion(adc_channel_t channel);

#endif	//ADC_H
