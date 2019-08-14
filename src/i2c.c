
#include <libopencm3/stm32/i2c.h>
#include <stdint.h>
#include "uart.h"

void i2c_setup() {
    I2C_CR2(I2C1) |= 36;
    I2C_CCR(I2C1) |= 180;
    I2C_TRISE(I2C1) = 37;
    I2C_CR1(I2C1) |= I2C_CR1_PE;
}

uint8_t i2c_start(uint32_t i2c, uint8_t addr, uint8_t mode) {
    I2C_CR1(i2c) |= I2C_CR1_START;
    while (!(I2C_SR1(i2c) & I2C_SR1_SB)) continue;
    I2C_DR(i2c) = (addr << 1) | mode;
    uint16_t timeout = 65535;
    while (!(I2C_SR1(i2c) & I2C_SR1_ADDR))
        if (!timeout--) {
            I2C_CR1(i2c) |= I2C_CR1_STOP;
            return 1;
        }
    (void)I2C_SR2(i2c);
    return 0;
}

void i2c_stop(uint32_t i2c) { I2C_CR1(i2c) |= I2C_CR1_STOP; }

void i2c_write(uint32_t i2c, uint8_t data) {
    I2C_DR(i2c) = data;
    while (!(I2C_SR1(i2c) & (I2C_SR1_TxE))) continue;
}

uint8_t i2c_read(uint32_t i2c){
    while (!(I2C_SR1(i2c) & (I2C_SR1_RxNE))) continue;
    return I2C_DR(i2c);
}