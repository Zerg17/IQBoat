#ifndef MAIN
#define MAIN

#include <stdint.h>
#include "ubx6.h"

extern volatile uint8_t activ;
extern volatile uint16_t u[4];
extern volatile uint16_t up;
extern NAV_POSLLH POSLLH;
extern NAV_VELNED VELNED;

extern uint8_t dma_gps_class, dma_gps_id;
extern char bufC[64];
extern uint8_t uart_buf[256];

#endif