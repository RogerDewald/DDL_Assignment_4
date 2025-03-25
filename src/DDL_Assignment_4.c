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

#define I2C0CONSET (*(volatile int *)0x4001C000)
#define I2C0STAT (*(volatile int *)0x4001C004)
#define I2C0ADR0 (*(volatile int *)0x4001C00C)
#define I2C0SCLH (*(volatile int *)0x4001C010)
#define I2C0SCLL (*(volatile int *)0x4001C014)
#define I2C0DAT (*(volatile int *)0x4001C008)
#define I2C0CONCLR (*(volatile int *)0x4001C018)

#define I2C1CONSET (*(volatile int *)0x4005C000)
#define I2C1STAT (*(volatile int *)0x4005C004)
#define I2C1ADR0 (*(volatile int *)0x4005C00C)
#define I2C1SCLH (*(volatile int *)0x4005C010)
#define I2C1SCLL (*(volatile int *)0x4005C014)
#define I2C1DAT (*(volatile int *)0x4005C008)
#define I2C1CONCLR (*(volatile int *)0x400A0018)

#define TEMP_ADDRESS (0b1001000 << 1)
#define EXPANDER_ADDRESS (0x20 << 1)

#define CONSET_AA (1 << 2)
#define CONSET_SI (1 << 3)
#define CONSET_STO (1 << 4)
#define CONSET_STA (1 << 5)
#define CONSET_I2EN (1 << 6)

#define CONCLR_AAC (1 << 2)
#define CONCLR_SIC (1 << 3)
#define CONCLR_STAC (1 << 5)
#define CONCLR_I2ENC (1 << 6)

#define EXPANDER_IODIRA 0x00
#define EXPANDER_IODIRB 0x01
#define EXPANDER_GPIOA 0x12
#define EXPANDER_GPIOB 0x13

#define PINMODE0 (*(volatile int *) 0x4002C040)
#define PINMODE1 (*(volatile int *) 0x4002C044)

#include <time.h>

volatile int units = 1;

void Start0() {
    I2C0CONSET = CONSET_STA;
    I2C0CONCLR = CONCLR_SIC;
    while (!(I2C0STAT == 0xF8)) {
    }
    I2C0CONCLR = CONCLR_STAC;
}
void Stop0() {
    I2C0CONSET = CONSET_STO;
    I2C0CONCLR = CONCLR_SIC;
}

int Write0(int data) {
    I2C0DAT = data;
    I2C0CONCLR = CONCLR_SIC;
    while (!(I2C0STAT == 0xF8)) {
    }
    return I2C0STAT;
}

int Read0(int ack) {
    if (ack)
        I2C0CONSET = CONSET_AA;
    else
        I2C0CONCLR = CONCLR_AAC;
    I2C0CONCLR = CONCLR_SIC;
    while (!(I2C0STAT == 0xF8)) {
    }
    return I2C0DAT & 0x0000000000FF;
}
void Start1() {
    I2C0CONSET = CONSET_STA;
    I2C0CONCLR = CONCLR_SIC;
    while (!(I2C0CONSET & CONSET_SI)) {
    }
    I2C0CONCLR = CONCLR_STAC;
}
void Stop1() {
    I2C0CONSET = CONSET_STO;
    I2C0CONCLR = CONCLR_SIC;
}

int Write1(int data) {
    I2C0DAT = data;
    I2C0CONCLR = CONCLR_SIC;
    while (!(I2C0CONSET & CONSET_SI)) {
    }
    return I2C0STAT;
}

int Read1(int ack) {
    if (ack)
        I2C1CONSET = CONSET_AA;
    else
        I2C1CONCLR = CONCLR_AAC;
    I2C1CONCLR = CONCLR_SIC;
    while (!(I2C1CONSET & CONSET_SI)) {
    }
    return I2C1DAT;
}

void Expander_Write(int reg, int data) {
    Start1();
    Write1(EXPANDER_ADDRESS | 0);
    Write1(reg);
    Write1(data);
    Stop1();
}

int Expander_Read(int reg) {
    int data;
    Start1();
    Write1(EXPANDER_ADDRESS | 0);
    Write1(reg);
    Start1();
    Write1(EXPANDER_ADDRESS | 1);
    data = Read1(0);
    Stop1();
    return data;
}

int Temp_Read_Cel(void) {
    int MSB;
    int LSB;
    Start0();
    Write0(TEMP_ADDRESS | 0);
    Write0(0x00);
    Start0();
    Write0(TEMP_ADDRESS | 1);
    MSB = Read0(1);
    LSB = Read0(0);
    Stop0();
    return ((MSB << 8) | (LSB)) >> 5;
}

void Initialization() {
	PINMODE0 |= (1 << 0);
	PINMODE0 |= (1 << 1);
	PINMODE0 |= (1 << 2);
	PINMODE0 |= (1 << 3);

	PINMODE1 &= ~(1 << 23);
	PINMODE1 |= (1 << 22);
	PINMODE1 &= ~(1 << 25);
	PINMODE1 |= (1 << 24);

    I2C0SCLH = 5;
    I2C0SCLL = 5;

    I2C1SCLH = 5;
    I2C1SCLL = 5;

    I2C0CONSET = CONSET_I2EN;

    //Expander_Write(EXPANDER_IODIRA, 0x00);
    //Expander_Write(EXPANDER_IODIRB, 0xFF);
}

int Convert(int temp) {
    return (int)(temp * 9.0 / 5.0) + 32;
}

void Wait(float secs) {
    volatile float sec_count = secs * 9e6;
    clock_t start_time = clock();
    while(clock() - start_time < sec_count){}
}

int BinaryDecimal(int n)
{
    int num = n;
    int dec_value = 0;
    int base = 1;
    int temp = num;

    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return dec_value;
}

int main(void) {
    Initialization();
    float temp_c;
    int temp_f;
    int intermediate;

    while (1) {

        intermediate = BinaryDecimal(Temp_Read_Cel());
        temp_c = intermediate * 0.125;
        temp_f = Convert(temp_c);
        if (temp_f > 99) {
            temp_f = 99;
        }
        if (temp_f < 0) {
            temp_f = 0;
        }
        if (units){
        }
        else {
        }
    }
    return 0;
}
