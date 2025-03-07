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

#define I2CO0NSET (*(volatile int *) 0x4001C000)
#define I2C0STAT (*(volatile int *) 0x4001C004)
#define I2C0ADR0 (*(volatile int *) 0x4001C00C)
#define I2C0SCLH (*(volatile int *) 0x4001C010)
#define I2C0SCLL (*(volatile int *) 0x4001C014)
#define I2C0DAT (*(volatile int *) 0x4001C008)

#define I2C2ONSET (*(volatile int *) 0x400AC000)
#define I2C2STAT (*(volatile int *) 0x400AC004)
#define I2C2ADR0 (*(volatile int *) 0x400AC00C)
#define I2C2SCLH (*(volatile int *) 0x400AC010)
#define I2C2SCLL (*(volatile int *) 0x400AC014)
#define I2C0DAT (*(volatile int *) 0x400AC008)

int main(void) {

	return 0;
}
