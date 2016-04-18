/*
 * Elektor project 130485 ADS1115 ADC board.
 *
 * Test project for driver.
 *
 * Author: CPV
 * Date: 29/04/2014
 *
 * Provided as is. Feel free to use, modify, redistribute, etc.
 */

// Include the bit-banged I2C driver.
#include "soft_i2c.h"

// Include the driver definition file.
#include "ads1x1x.h"
// Create an ADC object.
ADS1x1x_config_t my_adc;

int sda_pin = A4;
int scl_pin = A5;

// You must provide this function.
void soft_i2c_delay(void)
{
  delayMicroseconds(5);
}

// You must provide this function.
void soft_i2c_sda_mode(uint8_t value)
{
  if (value==0) pinMode(sda_pin,INPUT); // Use pull-ups on bus.
  else pinMode(sda_pin,OUTPUT);
}

// You must provide this function.
void soft_i2c_sda_write(uint8_t value)
{
  digitalWrite(sda_pin,value);
}

// You must provide this function.
uint8_t soft_i2c_sda_read(void)
{
  return digitalRead(sda_pin);
}

// You must provide this function.
void soft_i2c_scl_write(uint8_t value)
{
  digitalWrite(scl_pin,value);
}


// You must provide this function.
uint8_t ADS1x1x_i2c_start_write(uint8_t i2c_address)
{
  return soft_i2c_start_write(i2c_address);
}

// You must provide this function.
uint8_t ADS1x1x_i2c_write(uint8_t x)
{
  return soft_i2c_write(x);
}

// You must provide this function.
uint8_t ADS1x1x_i2c_start_read(uint8_t i2c_address, uint16_t bytes_to_read)
{
  return soft_i2c_start_read(i2c_address,bytes_to_read);
}

// You must provide this function.
uint8_t ADS1x1x_i2c_read(void)
{
  return soft_i2c_read();
}

// You must provide this function.
uint8_t ADS1x1x_i2c_stop(void)
{
  soft_i2c_stop();
  return 0;
}


void setup(void)
{
  Serial.begin(115200);
  Serial.println("130485 ADS1115 ADC board");
  Serial.println("(c) Elektor, 29/04/2014");
  Serial.println("");
  
  // Setup bit-banged I2C pins.
  pinMode(sda_pin,OUTPUT);
  pinMode(scl_pin,OUTPUT);

  // Initialise ADC object.
  if (ADS1x1x_init(&my_adc,ADS1115,ADS1x1x_I2C_ADDRESS_ADDR_TO_GND,MUX_SINGLE_0,PGA_4096)==0)
  {
    Serial.println("Could not initialise ADC structure.");
  }
}


void loop(void)
{
  // Loop over all possible input combinations.
  for (unsigned int input=0; input<0x8000; input+=0x1000)
  {
    // Set input before starting conversion.
    ADS1x1x_set_multiplexer(&my_adc,(ADS1x1x_mux_t)input);
    ADS1x1x_start_conversion(&my_adc);
    // Default sample rate is 128 samples/s, i.e. one sample every 7.8 ms.
    delay(8);
    // Display result as voltage (remember, the PGA was set to 4.096 V
    Serial.println((float)ADS1x1x_read(&my_adc)*4.096/32767.0);
    //Serial.println(ADS1x1x_read(&my_adc)); // print raw value
  }
  Serial.println("---");
  delay(500);
}

