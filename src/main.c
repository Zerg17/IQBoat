#include <libopencm3/stm32/i2c.h>
#include "compass.h"
#include "delay.h"
#include "lora.h"
#include "move.h"
#include "rc.h"
#include "system.h"
#include "uart.h"
#include "ubx6.h"

NAV_POSLLH POSLLH;
NAV_VELNED VELNED;

uint8_t dma_gps_class, dma_gps_id;
char bufC[64];
uint8_t uart_buf[256];

uint8_t i2c_check(uint32_t i2c, uint8_t address, uint8_t mode) {
    i2c_send_start(i2c);
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) &
             (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))))
        ;

    i2c_send_7bit_address(i2c, address, mode);

    int timeout = 20000;
    while (!(I2C_SR1(i2c) & I2C_SR1_ADDR)) {
        if (timeout > 0) {
            timeout--;
        } else {
            i2c_send_stop(i2c);
            return 1;
        }
    }
    
	(void)I2C_SR2(I2C1);
    
	return 0;
}

int main(void) {
    system_setup();
    move_setup();
    // lora_setup();
    usart_print("System start\n");

    // sprintf(bufC, "0x%02X\n", writeRegister(REG_VERSION));
    // usart_print(bufC);

    // USART_BRR(USART1) = rcc_apb2_frequency / 9600 + 1;
    // USART_CR1(USART1) |= USART_CR1_UE | USART_CR1_RE | USART_CR1_RXNEIE;
    // DMA_CPAR(DMA1, DMA_CHANNEL6) = (uint32_t)uart_buf;
    // DMA_CCR(DMA1, DMA_CHANNEL6) = DMA_CCR_MEM2MEM | DMA_CCR_MSIZE_8BIT |
    //                               DMA_CCR_PSIZE_8BIT | DMA_CCR_MINC |
    //                               DMA_CCR_PINC | DMA_CCR_TCIE;
    // nvic_enable_irq(NVIC_DMA1_CHANNEL6_IRQ);

    // for(uint8_t i=0; i<128; i++){
    //     sprintf(bufC, "ADDR=0x%02X, chek=%d\n", i, i2c_check(I2C1, i, 0));
    //     usart_print(bufC);
    //     _delay_ms(2);
    // }

    compas_write(2, 0);
    system_start();

    while (1) {
        uint8_t buf[6];
        compas_reads(3, buf, 6);
        int16_t x = buf[0] << 8 | buf[1];
        int16_t z = buf[2] << 8 | buf[3];
        int16_t y = buf[4] << 8 | buf[5];

        sprintf(bufC, "%i %i %i\n", x, y, z);
        usart_print(bufC);
        // sprintf(bufC, "%f\n", atan2(y, x)*(180/3.141528));

        // beginPacket();
        // lora_write((uint8_t*)u, 8);
        // endPacket();
        // _delay_ms(200);
    }
}