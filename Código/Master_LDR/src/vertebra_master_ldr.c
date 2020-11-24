#include "vertebra_master_ldr.h"
#include "i2c_master_functions.h"

//Flag de interrupción del Timer 1
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
void Read_Slave_Sensors(uint8_t esclavo){
    uint8_t valor1,valor2,valor3,valor4;
    uint16_t valorLuz,valorLuz2;
    
    //Lectura del Byte alto y bajo de los sensores
    valor1= I2C_Read1ByteRegister(esclavo,DAT1_REG);
    valor2 = I2C_Read1ByteRegister(esclavo,DAT2_REG);
    valorLuz= ((uint16_t)((valor1 << 8) + valor2));
    
    valor3= I2C_Read1ByteRegister(esclavo,DAT3_REG);
    valor4 = I2C_Read1ByteRegister(esclavo,DAT4_REG);
    valorLuz2= ((uint16_t)((valor3 << 8) + valor4));
    
    //Movimiento de los servos de acuerdo al valor del sensor
    if (valorLuz > 512 && valorLuz2 < 512){
        
        I2C_Write1ByteRegister(esclavo,PWM_REG,cicloMin);
    }
    else if(valorLuz < 512 && valorLuz2 > 512)
    {
        I2C_Write1ByteRegister(esclavo,PWM_REG,cicloMax);
    }
    else if(valorLuz > 512 && valorLuz2 > 512)
    {
        I2C_Write1ByteRegister(esclavo,PWM_REG,cicloReposo);
    }
    else
    {
        I2C_Write1ByteRegister(esclavo,PWM_REG,cicloReposo);
    }
}

void Read_All_Slave_Sensors(void){
    int n=0;
    //Recorre todos los módulos de acción
    while(n<NUMERO_ESCLAVOS){
        Read_Slave_Sensors(31+n);
        n++;
    }
}