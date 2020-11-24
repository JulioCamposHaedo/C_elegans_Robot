#include "i2c_master_functions.h"

typedef struct
{
    size_t len;
    uint8_t *data;
}i2c_buffer_t;

static i2c_operations_t rd1RegCompleteHandler(void *ptr);
static i2c_operations_t wr1RegCompleteHandler(void *ptr);


uint8_t I2C_Read1ByteRegister(i2c_address_t address, uint8_t reg)
{
    uint8_t returnValue = 0x00;
    
    while(!I2C_Open(address)); // sit here until we get the bus..
    I2C_SetDataCompleteCallback(rd1RegCompleteHandler,&returnValue);
    I2C_SetBuffer(&reg,1);
    I2C_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C_MasterWrite();
    while(I2C_BUSY == I2C_Close()); // sit here until finished.
    
    return returnValue;
}

void I2C_Write1ByteRegister(i2c_address_t address, uint8_t reg, uint8_t data)
{
    while(!I2C_Open(address)); // sit here until we get the bus..
    I2C_SetDataCompleteCallback(wr1RegCompleteHandler,&data);
    I2C_SetBuffer(&reg,1);
    I2C_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C_MasterWrite();
    while(I2C_BUSY == I2C_Close()); // sit here until finished.
}

static i2c_operations_t rd1RegCompleteHandler(void *ptr)
{
    I2C_SetBuffer(ptr,1);
    I2C_SetDataCompleteCallback(NULL,NULL);
    return I2C_RESTART_READ;
}

static i2c_operations_t wr1RegCompleteHandler(void *ptr)
{
    I2C_SetBuffer(ptr,1);
    I2C_SetDataCompleteCallback(NULL,NULL);
    return I2C_CONTINUE;
}
