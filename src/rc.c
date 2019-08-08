#include "rc.h"
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include "delay.h"

volatile uint16_t rc_activ = 0xFFFF;
volatile uint16_t u[4] = {1500, 1500, 1000, 1000};

// Проверяет активность пульта
uint8_t rc_check() {
    return !(
        ((rc_activ & 0x000F) == 0x000F) || ((rc_activ & 0x00F0) == 0x00F0) ||
        ((rc_activ & 0x0F00) == 0x0F00) || ((rc_activ & 0xF000) == 0xF000));
}

// Прозволяет определить отсутствие активности
void rc_update() {
    if (rc_check())
        rc_activ += 0x1111;
    else {
        u[0] = 1500;
        u[1] = 1500;
        u[2] = 1000;
        u[3] = 1000;
    }
}

// Обработчик изменений состояний на каналах RC приемника
void exti15_10_isr() {
    static uint32_t ul[4];
    uint32_t sysTime = DWT_CYCCNT;
    if (exti_get_flag_status(EXTI12)) {
        exti_reset_request(EXTI12);
        if (!gpio_get(GPIOB, GPIO12)) {
            uint16_t uz = (sysTime - ul[0]) / 72;
            if (uz > 800 && uz < 2200) {
                u[0] = uz;
                rc_activ &= 0xFFF0;
            }
        } else
            ul[0] = sysTime;
    }

    if (exti_get_flag_status(EXTI13)) {
        exti_reset_request(EXTI13);
        if (!gpio_get(GPIOB, GPIO13)) {
            uint16_t uz = (sysTime - ul[1]) / 72;
            if (uz > 800 && uz < 2200) {
                u[1] = uz;
                rc_activ &= 0xFF0F;
            }
        } else
            ul[1] = sysTime;
    }

    if (exti_get_flag_status(EXTI14)) {
        exti_reset_request(EXTI14);
        if (!gpio_get(GPIOB, GPIO14)) {
            uint16_t uz = (sysTime - ul[2]) / 72;
            if (uz > 800 && uz < 2200) {
                u[2] = uz;
                rc_activ &= 0xF0FF;
            }
        } else
            ul[2] = sysTime;
    }

    if (exti_get_flag_status(EXTI15)) {
        exti_reset_request(EXTI15);
        if (!gpio_get(GPIOB, GPIO15)) {
            uint16_t uz = (sysTime - ul[3]) / 72;
            if (uz > 800 && uz < 2200) {
                u[3] = uz;
                rc_activ &= 0x0FFF;
            }
        } else
            ul[3] = sysTime;
    }
}