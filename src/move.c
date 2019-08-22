#include "move.h"
#include <libopencm3/stm32/timer.h>
#include "tool.h"

void move_setup() {
    timer_enable_preload(TIM3);
    TIM_CCER(TIM3) |=
        TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
    timer_set_oc_mode(TIM3, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC4, TIM_OCM_PWM1);
    timer_set_period(TIM3, 10000);
    timer_set_prescaler(TIM3, 3);
    timer_enable_counter(TIM3);
}

void move(int16_t m1, int16_t m2) {
    m1 = constrain(m1, -10000, 10000);
    m2 = constrain(m2, -10000, 10000);
    if (abs(m1) < 100) m1 = 0;
    if (abs(m2) < 100) m2 = 0;

    TIM_CCR1(TIM3) = m1 > 0 ? m1 : 0;
    TIM_CCR2(TIM3) = m1 < 0 ? -m1 : 0;
    TIM_CCR3(TIM3) = m2 > 0 ? m2 : 0;
    TIM_CCR4(TIM3) = m2 < 0 ? -m2 : 0;
}

