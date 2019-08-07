#ifndef SYSTEM
#define SYSTEM

#include <stdint.h>

extern volatile uint32_t millis;

void system_setup();
void system_start();

#endif