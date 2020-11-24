/**
 * Autor: Julio Campos Haedo
 * Universisdad: Universidad Nacional de Rio Negro
 * 
 * Prototipo de módulo de comunicación.
 * Encargado de la lectura de los sensores de los módulos de acción.
 * Luego de la lectura de los sensores, le envía a cada esclavo un valor correspondiente
 * a la posición que deben tomar los servomotores.
 */

#include "init.h"
#include "vertebra_master_ldr.h"


void main(void)
{
    // Inicialización del dispositivo
    SYSTEM_Initialize();

    //Habilitación de interrupciones globales
    INTERRUPT_GlobalInterruptEnable();

    // Habilitación de interrupciones de periféricos
    INTERRUPT_PeripheralInterruptEnable();
    
    //Loop principal- Espera el evento de Timer1 para leer los registros de sensores de los modulos de accion.
    while (1)
    {
        if (Get_Master_TMR1_flag())
        {
             Read_All_Slave_Sensors();
             Clear_Master_TMR1_flag();
        } 
    }
}
