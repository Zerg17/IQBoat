#include "system.h"

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/i2c.h>
#include <stdio.h>
#include "delay.h"
#include "uart.h"
#include "move.h"

volatile uint32_t millis;

static void clock_setup(void) {
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    delayInit();
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_AFIO);

    rcc_periph_clock_enable(RCC_TIM3);
    rcc_periph_clock_enable(RCC_ADC1);
    rcc_periph_clock_enable(RCC_DMA1);
    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_USART2);
    rcc_periph_clock_enable(RCC_SPI1);
    rcc_periph_clock_enable(RCC_I2C1);
}

static void systick_setup(void) {
    nvic_set_priority(NVIC_SYSTICK_IRQ, 0x10);
    systick_set_reload(89999);
}

static void exti_setup(void) {
    exti_select_source(GPIO12 | GPIO13 | GPIO14 | GPIO15, GPIOB);
    exti_set_trigger(GPIO12 | GPIO13 | GPIO14 | GPIO15, EXTI_TRIGGER_BOTH);
    exti_enable_request(GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

static void gpio_setup(void) {
    // Пульт
    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN,
                  GPIO12 | GPIO13 | GPIO14 | GPIO15);

    // Измерение напряжения
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO4);

    // LoRa
    AFIO_MAPR |= AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON | AFIO_MAPR_SPI1_REMAP;
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                  GPIO_SPI1_RE_SCK | GPIO_SPI1_RE_MOSI);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
                  GPIO15 | GPIO11);

    // Uart debug
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART2_TX);

    // GPS
    AFIO_MAPR |= AFIO_MAPR_USART1_REMAP;
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_RE_TX);

    // Движки
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                  GPIO_TIM3_CH1 | GPIO_TIM3_CH2);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                  GPIO_TIM3_CH3 | GPIO_TIM3_CH4);

    // Компас
    AFIO_MAPR |= AFIO_MAPR_I2C1_REMAP;
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
                  GPIO_I2C1_RE_SCL | GPIO_I2C1_RE_SDA);
}

// static void adc_setup(void) {
//     ADC_CR2(ADC1) |= ADC_CR2_ADON | ADC_CR2_CAL;
//     while (ADC_CR2(ADC1) & ADC_CR2_CAL)
//         ;
//     ADC_SMPR2(ADC1) |= ADC_SMPR_SMP_239DOT5CYC;
//     ADC_CR2(ADC1) |= ADC_CR2_EXTSEL_SWSTART | ADC_CR2_EXTTRIG | ADC_CR2_CONT;
//     ADC_SQR3(ADC1) = 0x00000004;
//     ADC_CR2(ADC1) |= ADC_CR2_SWSTART;
// }

static void spi_setup(void) {
    SPI_CR1(SPI1) = SPI_CR1_MSTR | SPI_CR1_BAUDRATE_FPCLK_DIV_256 |
                    SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE;
}

static void i2c_setup() {
    I2C_CR2(I2C1) |= I2C_CR2_FREQ_36MHZ;
    I2C_CCR(I2C1) |= I2C_CCR_FS | 0x1e;
    I2C_TRISE(I2C1) = 0x0b;
    I2C_CR1(I2C1) |= I2C_CR1_PE;
}

static void nvic_start(void) {
    systick_interrupt_enable();
    nvic_enable_irq(NVIC_USART1_IRQ);
    nvic_enable_irq(NVIC_EXTI15_10_IRQ);
}

void system_setup() {
    clock_setup();
    systick_setup();
    exti_setup();
    usart_setup();
    // adc_setup();
    gpio_setup();
    spi_setup();
    i2c_setup();
}

void system_start() {
    nvic_start();
    systick_counter_enable();
}