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

volatile uint8_t activ = 0;
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