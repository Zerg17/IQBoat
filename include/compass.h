#ifndef COMPASS
#define COMPASS

#include <stdint.h>

#define COMPASS_ADDR 0x1E

uint8_t compas_read(uint8_t reg_addr);
void compas_reads(uint8_t reg_addr, uint8_t* res, uint16_t n);
void compas_write(uint8_t reg_addr, uint8_t data);

#endif