#ifndef RC
#define RC

#include <stdint.h>

extern volatile uint16_t u[4];

uint8_t rc_check();
void rc_update();

#endif