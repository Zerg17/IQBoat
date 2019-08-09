#include "compass.h"
#include <libopencm3/stm32/i2c.h>
#include <stdint.h>
#include "tool.h"
#include "uart.h"

uint8_t compas_read(uint8_t reg_addr) {
    I2C_CR1(I2C1) |= I2C_CR1_START;
    while (!(I2C_SR1(I2C1) & I2C_SR1_SB)) continue;
    i2c_send_7bit_address(I2C1, COMPASS_ADDR, I2C_WRITE);
    waitR(I2C_SR1(I2C1), I2C_SR1_ADDR);
    (void)I2C_SR2(I2C1);
    I2C_DR(I2C1) = reg_addr;
    waitR(I2C_SR1(I2C1), I2C_SR1_TxE);
    I2C_CR1(I2C1) |= I2C_CR1_START;
    waitR(I2C_SR1(I2C1), I2C_SR1_SB);
    i2c_send_7bit_address(I2C1, COMPASS_ADDR, I2C_READ);
    waitR(I2C_SR1(I2C1), I2C_SR1_ADDR);
    (void)I2C_SR2(I2C1);
    I2C_SR1(I2C1) &= ~I2C_CR1_ACK;
    waitR(I2C_SR1(I2C1), I2C_SR1_RxNE);
    uint8_t data = I2C_DR(I2C1);
    I2C_CR1(I2C1) |= I2C_CR1_STOP;
    return data;
}

void compas_reads(uint8_t reg_addr, uint8_t* res,
               uint16_t n) {
    I2C_CR1(I2C1) |= I2C_CR1_START;
    waitR(I2C_SR1(I2C1), I2C_SR1_SB);
    I2C_DR(I2C1) = COMPASS_ADDR << 1;
    waitR(I2C_SR1(I2C1), I2C_SR1_ADDR);
    (void)I2C_SR2(I2C1);
    I2C_DR(I2C1) = reg_addr;
    waitR(I2C_SR1(I2C1), I2C_SR1_TxE);
    I2C_CR1(I2C1) |= I2C_CR1_START | I2C_CR1_ACK;
    waitR(I2C_SR1(I2C1), I2C_SR1_SB);
    I2C_DR(I2C1) = COMPASS_ADDR << 1 | 1;
    waitR(I2C_SR1(I2C1), I2C_SR1_ADDR);
    (void)I2C_SR2(I2C1);
    for (uint16_t i = 0; i < n; ++i) {
        if (i == n - 1) I2C_CR1(I2C1) &= ~I2C_CR1_ACK;
        waitR(I2C_SR1(I2C1), I2C_SR1_RxNE);
        res[i] = I2C_DR(I2C1);
    }
    I2C_CR1(I2C1) |= I2C_CR1_STOP;
}

void compas_write(uint8_t reg_addr, uint8_t data) {
    I2C_CR1(I2C1) |= I2C_CR1_START;
    waitR(I2C_SR1(I2C1), I2C_SR1_SB);
    I2C_DR(I2C1) = COMPASS_ADDR << 1;
    waitR(I2C_SR1(I2C1), I2C_SR1_ADDR);
    (void)I2C_SR2(I2C1);
    I2C_DR(I2C1) = reg_addr;
    waitR(I2C_SR1(I2C1), I2C_SR1_TxE);
    I2C_DR(I2C1) = data;
    waitR(I2C_SR1(I2C1), I2C_SR1_BTF);
    I2C_CR1(I2C1) |= I2C_CR1_STOP;
}