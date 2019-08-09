#include "uart.h"
#include "tool.h"

void uart_setup() {
    usart_set_baudrate(USART2, 115200);
    usart_set_mode(USART2, USART_MODE_TX);
    usart_enable_tx_dma(USART2);
    usart_enable(USART2);
    DMA_CPAR(DMA1, DMA_CHANNEL7) = (uint32_t)&USART_DR(USART2);
    DMA_CCR(DMA1, DMA_CHANNEL7) = DMA_CCR_DIR | DMA_CCR_MINC | DMA_CCR_EN;
}

void uart_wait() {
    while (DMA_CNDTR(DMA1, DMA_CHANNEL7)) continue;
}

void uart_print(char *data) { uart_write((uint8_t *)data, strl(data)); }

void uart_write(uint8_t *data, uint16_t len) {
    while (DMA_CNDTR(DMA1, DMA_CHANNEL7)) continue;
    DMA_CCR(DMA1, DMA_CHANNEL7) &= ~DMA_CCR_EN;
    DMA_CMAR(DMA1, DMA_CHANNEL7) = (uint32_t)data;
    DMA_CNDTR(DMA1, DMA_CHANNEL7) = len;
    DMA_CCR(DMA1, DMA_CHANNEL7) |= DMA_CCR_EN;
}
