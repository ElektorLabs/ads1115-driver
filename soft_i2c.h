/**************************************************************************/
/*!
    @file     soft_i2c.h
    @author   CPV (Elektor), adapted from SoftI2C by Southern Storm Software, Pty Ltd.
    @license  see below

    Bit-banged I2C driver.

    v1.0 - First release
*/    
/*
 * Copyright (C) 2012 Southern Storm Software, Pty Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/**************************************************************************/

#ifndef __SOFT_I2C_H__
#define __SOFT_I2C_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * \brief Bit-banged implementation of an I2C master.
 *
 * This class implements the I2C master protocol on any arbitrary pair
 * of data and clock pins.
 *
 * This implementation only implements the master side of the protocol.
 * It assumes that there is a single bus master, no arbitration, and
 * no clock stretching.
 */


// Stubs to be implemented by you (the user).
extern void soft_i2c_delay(void);
extern void soft_i2c_sda_mode(uint8_t value);
extern void soft_i2c_sda_write(uint8_t value);
extern uint8_t soft_i2c_sda_read(void);
extern void soft_i2c_scl_write(uint8_t value);


void soft_i2c_init(void);
void soft_i2c_start(void);
void soft_i2c_stop(void);
uint8_t soft_i2c_start_write(uint8_t address);
uint8_t soft_i2c_write(uint8_t value);
uint8_t soft_i2c_start_read(uint8_t address, unsigned int count);
unsigned int soft_i2c_available(void);
uint8_t soft_i2c_read(void);
void soft_i2c_write_bit(uint8_t bit);
uint8_t soft_i2c_read_bit(void);


#ifdef __cplusplus
}
#endif

#endif // __SOFT_I2C_H__
