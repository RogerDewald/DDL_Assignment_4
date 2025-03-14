/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>

#define I2CO0NSET (*(volatile int *)0x4001C000)
#define I2C0STAT (*(volatile int *)0x4001C004)
#define I2C0ADR0 (*(volatile int *)0x4001C00C)
#define I2C0SCLH (*(volatile int *)0x4001C010)
#define I2C0SCLL (*(volatile int *)0x4001C014)
#define I2C0DAT (*(volatile int *)0x4001C008)
#define I2C0CONCLR (*(volatile int *)0x4001C018)

#define I2C1ONSET (*(volatile int *)0x4005C000)
#define I2C1STAT (*(volatile int *)0x4005C004)
#define I2C1ADR0 (*(volatile int *)0x4005C00C)
#define I2C1SCLH (*(volatile int *)0x4005C010)
#define I2C1SCLL (*(volatile int *)0x4005C014)
#define I2C1DAT (*(volatile int *)0x4005C008)
#define I2C1CONCLR (*(volatile int *)0x400A0018)

#define TEMP_ADDRESS (0x48 << 1)     // PCT2075 sensor
#define EXPANDER_ADDRESS (0x20 << 1) // MCP23017 I/O expander

#define CONSET_AA 0x04
#define CONSET_SI 0x08
#define CONSET_STO 0x10
#define CONSET_STA 0x20
#define CONSET_I2EN 0x40

#define CONCLR_AAC 0x04
#define CONCLR_SIC 0x08
#define CONCLR_STAC 0x20
#define CONCLR_I2ENC 0x40

#define EXPANDER_IODIRA 0x00
#define EXPANDER_IODIRB 0x01
#define EXPANDER_GPIOA 0x12
#define EXPANDER_GPIOB 0x13

int main(void) {
    return 0;
}
