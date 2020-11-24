#include "vertebra.h"
#include "i2c_master.h"
#include "i2c_master_functions.h"
#include <xc.h>

//Estructura de el estado de los movimientos del modulo
typedef enum
{
    SENO,
    COSENO,
    QUIETO            
}estado_movimiento_t;

//estado del movimiento
estado_movimiento_t estado_mov_viejo = SENO, estado_mov_nuevo = SENO;

//Valor representativo del duty cycle que se escribe en el registro PWM_REG del esclavo
uint8_t cicloMin = 15;
uint8_t cicloReposo = 45;
uint8_t cicloMax = 75;

//Cantidad de oscilaciones 
uint8_t ciclo;

//Flag por interrupción de TMR1
static uint8_t flag;

void TMR1_Master_InterruptHandler(void){
    flag = 1;
}

uint8_t Get_Master_TMR1_flag(void){
    return flag;
}

void Clear_Master_TMR1_flag(void){
    flag = 0;
}
void SetServo(i2c_address_t slave, uint8_t ciclo)
{
    I2C_Write1ByteRegister(slave,PWM_REG,ciclo);
}
void Rotar_Slave(uint8_t esclavo)
{
    //Cambio de los estados del movimiento
    if (ciclo < 8 && esclavo %2 ==0){
        estado_mov_nuevo = estado_mov_viejo; //Módulos adyancentes desfasados
    }
    if(ciclo > 8 && ciclo < 16 && esclavo %2!=0){//Módulos adyancentes en fase
        estado_mov_nuevo = estado_mov_viejo;
    }
    else if (ciclo > 16 ){
        estado_mov_nuevo =QUIETO;//Módulos en reposo, todos en linea recta
    }
    //Rutina que oscila el módulo de acción 
    switch(estado_mov_nuevo){
        case SENO:
            estado_mov_viejo = SENO;
            SetServo(esclavo,cicloMin);
            estado_mov_nuevo = COSENO;
            break;
        case COSENO:
            estado_mov_viejo = COSENO;
            SetServo(esclavo,cicloMax);
            estado_mov_nuevo = SENO;
            break;
        case QUIETO:
            estado_mov_viejo = QUIETO;
            SetServo(esclavo,cicloReposo);
            estado_mov_nuevo = QUIETO;
            break;
        default:
            break;   
    }
    ciclo=ciclo+1;
    
    //Reseteo del movimiento
    if(ciclo > 24){
        ciclo=0;
        estado_mov_viejo = SENO;
        estado_mov_nuevo = SENO;
    }
        
}
void Rotar_All_Slaves(void){
    int n=0;
    //Recorre todos los módulos de acción
    while(n<NUMERO_ESCLAVOS){
        Rotar_Slave(31+n);
        n++;
    }
}
