#ifndef I2C_MASTER_FUNCTIONS_H
#define I2C_MASTER_FUNCTIONS_H

#include <stdint.h>
#include <stdio.h>
#include "i2c_master.h"

void I2C_Write1ByteRegister(i2c_address_t address, uint8_t reg, uint8_t data);

#endif /* I2C_MASTER_FUNCTIONS_H */