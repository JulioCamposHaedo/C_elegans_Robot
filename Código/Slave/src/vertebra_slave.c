#include "vertebra_slave.h"
#include <xc.h>
#include "adc.h"
#include "i2c_slave.h"
#include "pwm1.h"
#include "pwm2.h"

//Flags de eventos
static uint8_t flag_tmr1; //Interrupción de TMR1
static uint8_t flag_i2c_reg; //Interrupción de I2C
static uint8_t flag_i2c_data; //Escritura en PWM_REG
static uint8_t write_reg; // Registro al cual se quiere leer/escribir

static datos_t d1; //Registros del esclavo

void Datos_Initialize(void)
{
    d1.dato1 = 1;
    d1.dato2 = 1;
    d1.dato3 = 1;
    d1.dato4 = 1;
    d1.ciclo = 45;
}

void TMR1_Slave_InterruptHandler(void){
    flag_tmr1 = 1;
}

uint8_t Get_TMR1_flag(void){
    return flag_tmr1;
}

void Clear_TMR1_flag(void){
    flag_tmr1 = 0;
}
void I2C_reg_Slave_InterruptHandler(uint8_t reg){
    flag_i2c_reg = 1;
    write_reg = reg;
}

uint8_t Get_I2C_reg_flag(void){
    return flag_i2c_reg;
}

uint8_t Get_I2C_reg(void){
    return write_reg;
}

void Clear_I2C_reg_flag(void){
    flag_i2c_reg = 0;
}
void I2C_data_slave_flag(void){
    flag_i2c_data = 1;
}

uint8_t Get_I2C_data_flag(void){
    return flag_i2c_data;
}

void Clear_I2C_data_flag(void){
    flag_i2c_data = 0;
}


void Read_Ldr(void)
{
    uint16_t Luz,Luz2;
    Luz=ADC_GetConversion(LDR_Left);
    d1.dato1 = ADRESH;
    d1.dato2 = ADRESL;
    Luz2=ADC_GetConversion(LDR_Right);
    d1.dato3 = ADRESH;
    d1.dato4 = ADRESL;
}

void I2C_Read_Write(uint8_t data){
    uint8_t i2c_WrData;
    //Si 
    if(Get_I2C_data_flag())
    {
        d1.ciclo = data;
        PWM1_LoadDutyValue(d1.ciclo);
        PWM2_LoadDutyValue(CYCLE_SUM_MAX-d1.ciclo);
        Clear_I2C_data_flag();
    }
    //Selección del registro al cual se quiere leer/escribir.
    switch (data)
    {
        case 1:
            i2c_WrData = d1.dato1;
            break;
        case 2:
            i2c_WrData = d1.dato2;
            break;
        case 3:
            i2c_WrData = d1.dato3;
            break;
        case 4:
            i2c_WrData = d1.dato4;
            break;
        case PWM_REG:
            I2C_data_slave_flag();
            break;
            
        default:
            break;    
    }
    Data_to_master(i2c_WrData);
}
