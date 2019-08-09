#ifndef I2C
#define I2C

#include <stdint.h>

uint8_t i2c_start(uint32_t i2c, uint8_t addr, uint8_t mode);
void i2c_stop(uint32_t i2c);
void i2c_write(uint32_t i2c, uint8_t reg, uint8_t data);

#endif