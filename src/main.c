#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "system.h"
#include "delay.h"
#include "lora.h"
#include "uart.h"
#include "tool.h"
#include "move.h"
#include "ubx6.h"

volatile uint32_t millis;
volatile uint8_t activ = 0;
uint32_t ul[4];
volatile uint16_t u[4] = {1500, 1500, 1000, 1000};
volatile uint16_t up = 0xFFFF;
NAV_POSLLH POSLLH;
NAV_VELNED VELNED;

uint8_t dma_gps_class, dma_gps_id;
char bufC[64];
uint8_t uart_buf[256];

int main(void) {
    system_setup();
    move_setup();
    lora_setup();
    usart_print("System start\n");

    // USART_BRR(USART1) = rcc_apb2_frequency / 9600 + 1;
    // USART_CR1(USART1) |= USART_CR1_UE | USART_CR1_RE | USART_CR1_RXNEIE;
    // DMA_CPAR(DMA1, DMA_CHANNEL6) = (uint32_t)uart_buf;
    // DMA_CCR(DMA1, DMA_CHANNEL6) = DMA_CCR_MEM2MEM | DMA_CCR_MSIZE_8BIT |
    //                               DMA_CCR_PSIZE_8BIT | DMA_CCR_MINC |
    //                               DMA_CCR_PINC | DMA_CCR_TCIE;
    // nvic_enable_irq(NVIC_DMA1_CHANNEL6_IRQ);

    system_start();
    while (1) {
        beginPacket();
        lora_write((uint8_t*)u, 8);
        endPacket();
        _delay_ms(500);
    }
}

void sys_tick_handler() {
    millis++;
    if (!(((up & 0x000F) == 0x000F) || ((up & 0x00F0) == 0x00F0) ||
          ((up & 0x0F00) == 0x0F00) || ((up & 0xF000) == 0xF000))) {
        up += 0x1111;
        activ = 1;
        int16_t s = mapc(u[1], 1100, 1900, -10000, 10000);
        int16_t a = mapc(u[0], 1100, 1900, -5000, 5000);

        if(!(millis%5)){
            //sprintf(bufC, "%u %u %u %u\n", u[0], u[1], u[2], u[3]);
            //usart_print(bufC);
        }
        move(s + a, s - a);
    } else {
        activ = 0;
        move(0, 0);
        u[0] = 0;
        u[1] = 0;
        u[2] = 0;
        u[3] = 0;
    }
}

#include "nvic.h"