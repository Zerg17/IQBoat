#include <libopencm3/stm32/i2c.h>
#include <stdio.h>
#include "compass.h"
#include "delay.h"
#include "i2c.h"
#include "lora.h"
#include "move.h"
#include "rc.h"
#include "system.h"
#include "uart.h"
#include "ubx6.h"

#define PI 3.14159265359

NAV_POSLLH POSLLH;
NAV_VELNED VELNED;

uint8_t dma_gps_class, dma_gps_id;
char bufC[64];
uint8_t uart_buf[256];

int16_t minX = 30000, maxX = -30000, minY = 30000, maxY = -30000, minZ = 30000, maxZ = -30000;
//int16_t minX = -125, maxX = 268, minY = 46, maxY = 443, minZ = 348, maxZ = 382;

int main(void) {
    system_setup();
    move_setup();
    // lora_setup();
    uart_print("System start\n");
    _delay_ms(10);

    // I2C_CR1(I2C1) |= I2C_CR1_START;
    // while (!(I2C_SR1(I2C1) & I2C_SR1_SB)) continue;
    // I2C_DR(I2C1) = 0x1E << 1;
    // while (!(I2C_SR1(I2C1) & I2C_SR1_ADDR)) continue;
    // (void)I2C_SR2(I2C1);
    // I2C_DR(I2C1) = 2;
    // while (!(I2C_SR1(I2C1) & I2C_SR1_TxE)) continue;
    // I2C_DR(I2C1) = 0;
    // while (!(I2C_SR1(I2C1) & I2C_SR1_BTF)) continue;
    // I2C_CR1(I2C1) |= I2C_CR1_STOP;

    // sprintf(bufC, "0x%02X\n", writeRegister(REG_VERSION));
    // usart_print(bufC);

    // USART_BRR(USART1) = rcc_apb2_frequency / 9600 + 1;
    // USART_CR1(USART1) |= USART_CR1_UE | USART_CR1_RE | USART_CR1_RXNEIE;
    // DMA_CPAR(DMA1, DMA_CHANNEL6) = (uint32_t)uart_buf;
    // DMA_CCR(DMA1, DMA_CHANNEL6) = DMA_CCR_MEM2MEM | DMA_CCR_MSIZE_8BIT |
    //                               DMA_CCR_PSIZE_8BIT | DMA_CCR_MINC |
    //                               DMA_CCR_PINC | DMA_CCR_TCIE;
    // nvic_enable_irq(NVIC_DMA1_CHANNEL6_IRQ);

    // if (!i2c_start(I2C1, 0x1E, I2C_WRITE)) {
    //     i2c_write(I2C1, 2);
    //     i2c_write(I2C1, 0);
    //     i2c_stop(I2C1);
    // }

    // for(uint8_t i=0; i<128; i++){
    //     uart_wait();
    //     sprintf(bufC, "ADDR=0x%02X, chek=%d\n", i, i2c_start(I2C1, i, 1));

    //     uart_print(bufC);
    //     //_delay_ms(2);
    // }

    // compas_write(2, 0);
    system_start();

    while (1) {
        uint8_t buf[6];

        // I2C_CR1(I2C1) |= I2C_CR1_START;
        // while (!(I2C_SR1(I2C1) & I2C_SR1_SB)) continue;
        // I2C_DR(I2C1) = 0x1E << 1;
        // while (!(I2C_SR1(I2C1) & I2C_SR1_ADDR)) continue;
        // (void)I2C_SR2(I2C1);
        // I2C_DR(I2C1) = 3;
        // while (!(I2C_SR1(I2C1) & I2C_SR1_TxE)) continue;
        // I2C_CR1(I2C1) |= I2C_CR1_START | I2C_CR1_ACK;
        // while (!(I2C_SR1(I2C1) & I2C_SR1_SB)) continue;
        // I2C_DR(I2C1) = 0x1E  << 1 | 1;
        // while (!(I2C_SR1(I2C1) & I2C_SR1_ADDR)) continue;
        // (void)I2C_SR2(I2C1);
        // for (size_t i = 0; i < 6; ++i) {
        //     if (i == 6 - 1) I2C_CR1(I2C1) &= ~I2C_CR1_ACK;
        //     while (!(I2C_SR1(I2C1) & I2C_SR1_RxNE)) continue;
        //     buf[i] = I2C_DR(I2C1);
        // }
        // I2C_CR1(I2C1) |= I2C_CR1_STOP;

        // int16_t x, y, z;
        // if (!i2c_start(I2C1, 0x1E, I2C_WRITE)) {
        //     i2c_write(I2C1, 3);
        //     I2C_CR1(I2C1) |= I2C_CR1_ACK;
        //     i2c_start(I2C1, 0x1E, I2C_READ);
        //     x = i2c_read(I2C1) << 8;
        //     x |= i2c_read(I2C1);
        //     z = i2c_read(I2C1) << 8;
        //     z |= i2c_read(I2C1);
        //     y = i2c_read(I2C1) << 8;
        //     I2C_CR1(I2C1) &= ~I2C_CR1_ACK;
        //     y |= i2c_read(I2C1);
        //     i2c_stop(I2C1);

        //     // if(x<minX)minX=x;
        //     // if(x>maxX)maxX=x;

        //     // if(y<minY)minY=y;
        //     // if(y>maxY)maxY=y;

        //     // if(z<minZ)minZ=z;
        //     // if(z>maxZ)maxZ=z;

        //     // x = map(x, minX, maxX, -1000, 1000);
        //     // y = map(y, minY, maxY, -1000, 1000);
        //     // z = map(z, minZ, maxZ, -1000, 1000);
        //     // float angle = atan2(y, x) + PI / 2; //+ 0.19693132;
        //     // if (angle < 0) angle += 2 * PI;
        //     // if (angle > 2 * PI) angle -= 2 * PI;

        //     sprintf(bufC, "%i %i %i\n", x, y, z);
        //     //sprintf(bufC, "%i %i %i %i %i %i\n", minX, maxX, minY, maxY, minZ, maxZ);
        //     //sprintf(bufC, "%f\n", angle * (180 / PI));
        //     uart_print(bufC);
        // }

        _delay_ms(70);

        // uint8_t buf[6];
        // compas_reads(3, buf, 6);
        // int16_t x = buf[0] << 8 | buf[1];
        // int16_t z = buf[2] << 8 | buf[3];
        // int16_t y = buf[4] << 8 | buf[5];

        // sprintf(bufC, "%i %i %i\n", x, y, z);
        // uart_print(bufC);
        // sprintf(bufC, "%f\n", atan2(y, x)*(180/3.141528));

        // beginPacket();
        // lora_write((uint8_t*)u, 8);
        // endPacket();
        // _delay_ms(200);

        
        //sprintf(bufC, "%u %u %u %u\n", u[0], u[1], u[2], u[3]);
        //uart_print(bufC);
    }
}