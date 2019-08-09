#ifndef UART
#define UART

#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <stdint.h>

void uart_setup();
void uart_print(char*);
void uart_write(uint8_t*, uint16_t len);
void uart_wait();


#endif