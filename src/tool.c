#include "tool.h"

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long mapc(long x, long in_min, long in_max, long out_min, long out_max) {
    return constrain((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min, out_min, out_max);
}

uint16_t strl(char *str) {
    uint16_t l = 0;
    while (*str++ != 0) l++;
    return l;
}