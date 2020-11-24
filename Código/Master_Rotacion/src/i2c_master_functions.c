#include "i2c_master_functions.h"

typedef struct
{
    size_t len;
    uint8_t *data;
}i2c_buffer_t;

static i2c_operations_t wr1RegCompleteHandler(void *ptr);


void I2C_Write1ByteRegister(i2c_address_t address, uint8_t reg, uint8_t data)
{
    while(!I2C_Open(address)); // Espera acá hasta obtner el bus
    I2C_SetDataCompleteCallback(wr1RegCompleteHandler,&data);
    I2C_SetBuffer(&reg,1);
    I2C_SetAddressNackCallback(NULL,NULL); //NACK polling
    I2C_MasterWrite();
    while(I2C_BUSY == I2C_Close()); // Eséra acá hasta que termine.
}

static i2c_operations_t wr1RegCompleteHandler(void *ptr)
{
    I2C_SetBuffer(ptr,1);
    I2C_SetDataCompleteCallback(NULL,NULL);
    return I2C_CONTINUE;
}
