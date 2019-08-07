#ifndef NVIC
#define NVIC

void exti15_10_isr() {
    uint32_t sysTime = DWT_CYCCNT;
    if (exti_get_flag_status(EXTI12)) {
        exti_reset_request(EXTI12);
        if (!gpio_get(GPIOB, GPIO12)) {
            uint16_t uz = (sysTime - ul[0]) / 72;
            if (uz > 800 && uz < 2200) {
                u[0] = uz;
                up &= 0xFFF0;
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
                up &= 0xFF0F;
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
                up &= 0xF0FF;
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
                up &= 0x0FFF;
            }
        } else
            ul[3] = sysTime;
    }
}

void dma1_channel6_isr() {
    if (DMA_ISR(DMA1) & DMA_ISR_TCIF6) {
        DMA_IFCR(DMA1) = DMA_IFCR_CIF(DMA_CHANNEL6);
        if (dma_gps_class == 0x01 && dma_gps_id == 0x02){
        //     sprintf(bufC, "%li %li %li %li\n", POSLLH.lon, POSLLH.lat,
        //             POSLLH.height, POSLLH.hMSL);
        // usart_print(bufC);
        }
    }
}

void usart1_isr() {
    static uint8_t stat = 0;
    static uint8_t gps_class, gps_id, gps_ck_a, gps_ck_b, ck_a, ck_b;
    static uint16_t gps_len, p;
    if ((USART_SR(USART1) & USART_SR_RXNE)) {
        uint8_t d = USART_DR(USART1);
        USART_DR(USART2) = d;
        if (stat >= 2 && stat <= 6) ck_a += d, ck_b += ck_a;
        switch (stat) {
            case 0: stat = (d == 0xB5) ? 1 : 0; break;
            case 1: stat = (d == 0x62) ? 2 : 0; break;
            case 2: gps_class = d, stat = 3; break;
            case 3: gps_id = d, stat = 4; break;
            case 4: gps_len = d, stat = 5; break;
            case 5: gps_len |= d << 8, p = 0, stat = 6; break;
            case 6: uart_buf[p++] = d, stat = (p == gps_len) ? 7 : 6; break;
            case 7: gps_ck_a = d, stat = 8; break;
            case 8: gps_ck_b = d, stat = 9; break;
            case 9:
                if (gps_ck_a == ck_a && gps_ck_b == ck_b) {
                    if (gps_class == 0x01 && gps_id == 0x02) {
                        DMA_CCR(DMA1, DMA_CHANNEL6) &= ~DMA_CCR_EN;
                        DMA_CNDTR(DMA1, DMA_CHANNEL6) = gps_len;
                        DMA_CMAR(DMA1, DMA_CHANNEL6) = (uint32_t)&POSLLH;
                        DMA_CCR(DMA1, DMA_CHANNEL6) |= DMA_CCR_EN;
                        dma_gps_class = gps_class, dma_gps_id = gps_id;
                    }
                    if (gps_class == 0x01 && gps_id == 0x12) {
                        DMA_CCR(DMA1, DMA_CHANNEL6) &= ~DMA_CCR_EN;
                        DMA_CNDTR(DMA1, DMA_CHANNEL6) = gps_len;
                        DMA_CMAR(DMA1, DMA_CHANNEL6) = (uint32_t)&VELNED;
                        DMA_CCR(DMA1, DMA_CHANNEL6) |= DMA_CCR_EN;
                        dma_gps_class = gps_class, dma_gps_id = gps_id;
                    }
                }
                ck_a = 0, ck_b = 0;
                stat = 0;
                break;
        }
    }
}

#endif