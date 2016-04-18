/**************************************************************************/
/*!
    @file     soft_i2c.c
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

#include "soft_i2c.h"


#define SOFT_I2C_INPUT  (0)
#define SOFT_I2C_OUTPUT  (1)
#define SOFT_I2C_LOW  (0)
#define SOFT_I2C_HIGH  (1)

static uint8_t soft_i2c_started;
static unsigned int soft_i2c_bytes_to_read;


void soft_i2c_init(void)
{
  // Make SDA an output.
  // SCL is supposed to be always an output.
  soft_i2c_sda_mode(SOFT_I2C_OUTPUT);
  // Put I2C bus in idle mode.
  soft_i2c_scl_write(SOFT_I2C_HIGH);
  soft_i2c_sda_write(SOFT_I2C_HIGH);
  // Initialise state variables.
  soft_i2c_started = 0;
  soft_i2c_bytes_to_read = 0;
}


void soft_i2c_start(void)
{
  soft_i2c_sda_mode(SOFT_I2C_OUTPUT);
  if (soft_i2c_started) 
  {
    // Already started, so send a restart condition.
    soft_i2c_sda_write(SOFT_I2C_HIGH);
    soft_i2c_scl_write(SOFT_I2C_HIGH);
    soft_i2c_delay();
  }
  soft_i2c_sda_write(SOFT_I2C_LOW);
  soft_i2c_delay();
  soft_i2c_scl_write(SOFT_I2C_LOW);
  soft_i2c_delay();
  soft_i2c_started = 1;
}


void soft_i2c_stop(void)
{
  soft_i2c_sda_mode(SOFT_I2C_OUTPUT);
  soft_i2c_sda_write(SOFT_I2C_LOW);
  soft_i2c_scl_write(SOFT_I2C_HIGH);
  soft_i2c_delay();
  soft_i2c_sda_write(SOFT_I2C_HIGH);
  soft_i2c_delay();
  soft_i2c_started = 0;
}


uint8_t soft_i2c_start_write(uint8_t address)
{
  soft_i2c_start();
  if (soft_i2c_write(address<<1)==0) return 0;
  return 1;
}


uint8_t soft_i2c_write(uint8_t value)
{
  uint8_t mask = 0x80;
  while (mask!=0) 
  {
    soft_i2c_write_bit((value&mask)!=0);
    mask >>= 1;
  }
  if (soft_i2c_read_bit()!=0) return 0;
  return 1;
}


uint8_t soft_i2c_start_read(uint8_t address, unsigned int count)
{
  soft_i2c_start();
  if (soft_i2c_write((address<<1)|0x01)==0)
  {
    soft_i2c_bytes_to_read = 0;
    return 0;
  }
  soft_i2c_bytes_to_read = count;
  return 1;
}


unsigned int soft_i2c_available(void)
{
  return soft_i2c_bytes_to_read;
}


uint8_t soft_i2c_read(void)
{
  uint8_t i;
  uint8_t value = 0;
  // Read 8 bits
  for (i=0; i<8; i++)
  {
    value = (value<<1) | soft_i2c_read_bit();
  }
  if (soft_i2c_bytes_to_read>1) 
  {
    // More bytes left to read - send an ACK.
    soft_i2c_write_bit(0);
    soft_i2c_bytes_to_read -= 1;
  } 
  else 
  {
    // Last byte - send the NACK and a stop condition.
    soft_i2c_write_bit(1);
    soft_i2c_stop();
    soft_i2c_bytes_to_read = 0;
  }
  return value;
}


void soft_i2c_write_bit(uint8_t bit)
{
  soft_i2c_sda_mode(SOFT_I2C_OUTPUT);
  soft_i2c_sda_write(bit);
  soft_i2c_delay();
  soft_i2c_scl_write(SOFT_I2C_HIGH);
  soft_i2c_delay();
  soft_i2c_scl_write(SOFT_I2C_LOW);
  soft_i2c_delay();
}


uint8_t soft_i2c_read_bit(void)
{
  soft_i2c_sda_mode(SOFT_I2C_INPUT);
  soft_i2c_sda_write(SOFT_I2C_HIGH);
  soft_i2c_scl_write(SOFT_I2C_HIGH);
  uint8_t bit = soft_i2c_sda_read();
  soft_i2c_delay();
  soft_i2c_scl_write(SOFT_I2C_LOW);
  soft_i2c_delay();
  return bit;
}
