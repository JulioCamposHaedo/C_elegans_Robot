/**
 * Autor: Julio Campos Haedo
 * Universisdad: Universidad Nacional de Rio Negro
 * 
 * Prototipo de módulo de comunicación.
 * Encargado de la poner a prueba el rango de rotación de los módulos de acción
 * con movimientos preestablecidos.
 * Banco de prueba de las oscilaciones del robot.
 */

#include "init.h"
#include "vertebra.h"

void main(void)
{
    // Inicialización del dispositivo
    SYSTEM_Initialize();
    
    //Habilitación de interrupciones globales
    INTERRUPT_GlobalInterruptEnable();

    // Habilitación de interrupciones de periféricos
    INTERRUPT_PeripheralInterruptEnable();
    
    //Loop principal- Espera el evennto de Timer 1 para girar los servomotores
    while (1)
    {
         if (Get_Master_TMR1_flag())
        {
             Rotar_All_Slaves();
             Clear_Master_TMR1_flag();
        }
    }
}
