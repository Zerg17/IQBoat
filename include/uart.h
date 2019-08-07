#ifndef UART
#define UART

#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <stdint.h>

void usart_setup();
void usart_print(char*);
void usart_write(uint8_t*, uint16_t len);


#endif