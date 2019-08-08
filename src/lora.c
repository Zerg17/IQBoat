#include "lora.h"
#include "delay.h"
#include "tool.h"

uint8_t singleTransfer(uint8_t, uint8_t);
uint8_t readRegister(uint8_t);
void writeRegister(uint8_t, uint8_t);
void setFrequency(long);
void setOCP(uint8_t);
void setTxPower(int);
bool isTransmitting();


uint8_t singleTransfer(uint8_t address, uint8_t value) {
    ResCS;
    spi_xfer(SPI1, address);
    uint8_t response = spi_xfer(SPI1, value);
    SetCS;
    return response;
}

uint8_t readRegister(uint8_t address) {
    return singleTransfer(address & 0x7f, 0x00);
}

void writeRegister(uint8_t address, uint8_t value) {
    singleTransfer(address | 0x80, value);
}

void setFrequency(long frequency) {
    uint64_t frf = ((uint64_t)frequency << 19) / 32000000;
    writeRegister(REG_FRF_MSB, (uint8_t)(frf >> 16));
    writeRegister(REG_FRF_MID, (uint8_t)(frf >> 8));
    writeRegister(REG_FRF_LSB, (uint8_t)(frf >> 0));
}

void setOCP(uint8_t mA) {
    uint8_t ocpTrim = 27;
    if (mA <= 120) {
        ocpTrim = (mA - 45) / 5;
    } else if (mA <= 240) {
        ocpTrim = (mA + 30) / 10;
    }
    writeRegister(REG_OCP, 0x20 | (0x1F & ocpTrim));
}

void setTxPower(int level) {
    if (level > 17) {
        if (level > 20) level = 20;
        level -= 3;
        writeRegister(REG_PA_DAC, 0x87);
        setOCP(140);
    } else {
        if (level < 2) level = 2;
        writeRegister(REG_PA_DAC, 0x84);
        setOCP(100);
    }
    writeRegister(REG_PA_CONFIG, PA_BOOST | (level - 2));
}

bool isTransmitting() {
    if ((readRegister(REG_OP_MODE) & MODE_TX) == MODE_TX) return true;
    if (readRegister(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK)
        writeRegister(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
    return false;
}

void beginPacket() {
    if (isTransmitting()) return;
    writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_STDBY);
    writeRegister(REG_MODEM_CONFIG_1, readRegister(REG_MODEM_CONFIG_1) & 0xfe);
    writeRegister(REG_FIFO_ADDR_PTR, 0);
    writeRegister(REG_PAYLOAD_LENGTH, 0);
}

uint8_t lora_write(const uint8_t *buffer, uint8_t size) {
    int currentLength = readRegister(REG_PAYLOAD_LENGTH);
    ResCS;
    spi_xfer(SPI1, REG_FIFO | 0x80);
    for (uint8_t i = 0; i < size; i++) spi_xfer(SPI1, buffer[i]);
    SetCS;
    writeRegister(REG_PAYLOAD_LENGTH, currentLength + size);
    return size;
}

uint8_t lora_print(char *buffer) {
    return lora_write((uint8_t*)buffer, strl(buffer));
}

void endPacket() {
    writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_TX);
    while ((readRegister(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK) == 0)
        ;
    writeRegister(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
}

void lora_setup() {
    SetCS;
    _delay_ms(10);
    SetReset;
    _delay_ms(10);
    writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_SLEEP);
    setFrequency(425E6);
    writeRegister(REG_FIFO_TX_BASE_ADDR, 0);
    writeRegister(REG_FIFO_RX_BASE_ADDR, 0);
    writeRegister(REG_LNA, readRegister(REG_LNA) | 0x03);
    writeRegister(REG_MODEM_CONFIG_3, 0x04);
    setTxPower(6);
    writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_STDBY);
}