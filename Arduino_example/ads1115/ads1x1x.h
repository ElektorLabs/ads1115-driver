/**************************************************************************/
/*!
    @file     ADS1x1x.h
    @author   CPV (Elektor)
    @license  BSD (see license.txt)

    Driver for the ADS101x/ADS111x Sigma-Delta Analog/Digital Converters.

    This started out as a port of the Adafruit library, but ended
    up largely rewritten.

    v1.0 - First release
*/
/**************************************************************************/

#ifndef __ADS1x1x_H__
#define __ADS1x1x_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


// I2C stubs, implementations to be provided by the user.
extern uint8_t ADS1x1x_i2c_start_write(uint8_t i2c_address);
extern uint8_t ADS1x1x_i2c_write(uint8_t x);
extern uint8_t ADS1x1x_i2c_start_read(uint8_t i2c_address, uint16_t bytes_to_read);
extern uint8_t ADS1x1x_i2c_read(void);
extern uint8_t ADS1x1x_i2c_stop(void);


// I2C definitions.
#define ADS1x1x_I2C_ADDRESS_ADDR_TO_GND  (0x48)
#define ADS1x1x_I2C_ADDRESS_ADDR_TO_VCC  (0x49)
#define ADS1x1x_I2C_ADDRESS_ADDR_TO_SDA  (0x4a)
#define ADS1x1x_I2C_ADDRESS_ADDR_TO_SCL  (0x4b)

// Chip "pointer" registers
#define ADS1x1x_REG_POINTER_MASK  (0x03)
#define ADS1x1x_REG_POINTER_CONVERSION  (0x00)
#define ADS1x1x_REG_POINTER_CONFIG  (0x01)
#define ADS1x1x_REG_POINTER_LO_THRESH  (0x02)
#define ADS1x1x_REG_POINTER_HI_THRESH  (0x03)

// Config register masks
#define ADS1x1x_REG_CONFIG_OS_MASK  (0x8000)
#define ADS1x1x_REG_CONFIG_MULTIPLEXER_MASK  (0x7000)
#define ADS1x1x_REG_CONFIG_PGA_MASK  (0x0E00)
#define ADS1x1x_REG_CONFIG_MODE_MASK  (0x0100)
#define ADS1x1x_REG_CONFIG_DATA_RATE_MASK  (0x00E0)
#define ADS1x1x_REG_CONFIG_COMPARATOR_MODE_MASK  (0x0010)
#define ADS1x1x_REG_CONFIG_COMPARATOR_POLARITY_MASK  (0x0008)
#define ADS1x1x_REG_CONFIG_COMPARATOR_LATCHING_MASK  (0x0004)  // Determines if ALERT/RDY pin latches once asserted
#define ADS1x1x_REG_CONFIG_COMPARATOR_QUEUE_MASK  (0x0003)

// Config register bits
#define ADS1x1x_REG_CONFIG_OS_IDLE  (0x8000)  // Read: bit = 1 when device is not performing a conversion

// The chips that we know of.
typedef enum
{
  ADS1013,
  ADS1014,
  ADS1015,
  ADS1113,
  ADS1114,
  ADS1115
}
ADS1x1x_chip_t;


// The following enums are to be used with the configuration functions.

typedef enum
{
  OS_SINGLE = 0x8000  // Single-conversion
}
ADS1x1x_os_t;

typedef enum
{
  MUX_DIFF_0_1 = 0x0000,  // Differential P = AIN0, N = AIN1 (default)
  MUX_DIFF_0_3 = 0x1000,  // Differential P = AIN0, N = AIN3
  MUX_DIFF_1_3 = 0x2000,  // Differential P = AIN1, N = AIN3
  MUX_DIFF_2_3 = 0x3000,  // Differential P = AIN2, N = AIN3
  MUX_SINGLE_0 = 0x4000,  // Single-ended AIN0
  MUX_SINGLE_1 = 0x5000,  // Single-ended AIN1
  MUX_SINGLE_2 = 0x6000,  // Single-ended AIN2
  MUX_SINGLE_3 = 0x7000   // Single-ended AIN3
}
ADS1x1x_mux_t;

typedef enum
{
  PGA_6144 = 0x0000,  // +/-6.144V range = Gain 2/3
  PGA_4096 = 0x0200,  // +/-4.096V range = Gain 1
  PGA_2048 = 0x0400,  // +/-2.048V range = Gain 2 (default)
  PGA_1024 = 0x0600,  // +/-1.024V range = Gain 4
  PGA_512 = 0x0800,  // +/-0.512V range = Gain 8
  PGA_256 = 0x0A00  // +/-0.256V range = Gain 16
}
ADS1x1x_pga_t;

typedef enum
{
  MODE_CONTINUOUS = 0x0000,  // Continuous conversion mode
  MODE_SINGLE_SHOT = 0x0100  // Power-down single-shot mode (default)
}
ADS1x1x_mode_t;

typedef enum
{
  // ADS101x
  DATA_RATE_ADS101x_128 = 0x0000,  // 128 samples per second
  DATA_RATE_ADS101x_250 = 0x0020,  // 250 samples per second
  DATA_RATE_ADS101x_490 = 0x0040,  // 490 samples per second
  DATA_RATE_ADS101x_920 = 0x0060,  // 920 samples per second
  DATA_RATE_ADS101x_1600 = 0x0080,  // 1600 samples per second (default)
  DATA_RATE_ADS101x_2400 = 0x00a0,  // 2400 samples per second
  DATA_RATE_ADS101x_3300 = 0x00c0,  // 3300 samples per second
  // ADS111x
  DATA_RATE_ADS111x_8 = 0x0000,  // 8 samples per second
  DATA_RATE_ADS111x_16 = 0x0020,  // 16 samples per second
  DATA_RATE_ADS111x_32 = 0x0040,  // 32 samples per second
  DATA_RATE_ADS111x_64 = 0x0060,  // 64 samples per second
  DATA_RATE_ADS111x_128 = 0x0080,  // 128 samples per second (default)
  DATA_RATE_ADS111x_250 = 0x00a0,  // 250 samples per second
  DATA_RATE_ADS111x_475 = 0x00c0,  // 475 samples per second
  DATA_RATE_ADS111x_860 = 0x00e0  // 860 samples per second
}
ADS1x1x_data_rate_t;

typedef enum
{
  COMPARATOR_MODE_TRADITIONAL = 0x0000,  // Traditional comparator with hysteresis (default)
  COMPARATOR_MODE_WINDOW = 0x0010  // Window comparator
}
ADS1x1x_comparator_mode_t;

typedef enum
{
  COMPARATOR_POLARITY_ACTIVE_LO = 0x0000,  // ALERT/RDY pin is low when active (default)
  COMPARATOR_POLARITY_ACTIVE_HI = 0x0008  // ALERT/RDY pin is high when active
}
ADS1x1x_comparator_polarity_t;

typedef enum
{
  COMPARATOR_NON_LATCHING = 0x0000,  // Non-latching comparator (default)
  COMPARATOR_LATCHING = 0x0004  // Latching comparator
}
ADS1x1x_comparator_latching_t;

typedef enum
{
  COMPARATOR_QUEUE_1 = 0x0000,  // Assert ALERT/RDY after one conversions
  COMPARATOR_QUEUE_2 = 0x0001,  // Assert ALERT/RDY after two conversions
  COMPARATOR_QUEUE_4 = 0x0002,  // Assert ALERT/RDY after four conversions
  COMPARATOR_QUEUE_NONE = 0x0003  // Disable the comparator and put ALERT/RDY in high state (default)
}
ADS1x1x_comparator_queue_t;


// You must declare this structure somewhere to use the ADC.
// You can have as many as you like.
typedef struct
{
  ADS1x1x_chip_t chip;
  uint8_t i2c_address;
  uint16_t config;
}
ADS1x1x_config_t;

// Easy usage:
// Call this at startup:
uint8_t ADS1x1x_init(ADS1x1x_config_t *p_config, ADS1x1x_chip_t chip, uint8_t i2c_address, ADS1x1x_mux_t input, ADS1x1x_pga_t gain);
// Then call:
void ADS1x1x_start_conversion(ADS1x1x_config_t *p_config);
// ... and wait a bit before calling this:
int16_t ADS1x1x_read(ADS1x1x_config_t *p_config);

// Configuration methods to call before calling ADS1x1x_start_conversion.
void ADS1x1x_set_threshold_lo(ADS1x1x_config_t *p_config, uint16_t value);
void ADS1x1x_set_threshold_hi(ADS1x1x_config_t *p_config, uint16_t value);
void ADS1x1x_set_os(ADS1x1x_config_t *p_config, ADS1x1x_os_t value);
void ADS1x1x_set_multiplexer(ADS1x1x_config_t *p_config, ADS1x1x_mux_t value);
void ADS1x1x_set_pga(ADS1x1x_config_t *p_config, ADS1x1x_pga_t value);
void ADS1x1x_set_mode(ADS1x1x_config_t *p_config, ADS1x1x_mode_t value);
void ADS1x1x_set_data_rate(ADS1x1x_config_t *p_config, ADS1x1x_data_rate_t value);
void ADS1x1x_set_comparator_mode(ADS1x1x_config_t *p_config, ADS1x1x_comparator_mode_t value);
void ADS1x1x_set_comparator_polarity(ADS1x1x_config_t *p_config, ADS1x1x_comparator_polarity_t value);
void ADS1x1x_set_comparator_latching(ADS1x1x_config_t *p_config, ADS1x1x_comparator_latching_t value);
void ADS1x1x_set_comparator_queue(ADS1x1x_config_t *p_config, ADS1x1x_comparator_queue_t value);

// Full control access.
void ADS1x1x_write_register(uint8_t i2c_address, uint8_t reg, uint16_t value);
uint16_t ADS1x1x_read_register(uint8_t i2c_address, uint8_t reg);
void ADS1x1x_set_config_bitfield(ADS1x1x_config_t *p_config, uint16_t value, uint16_t mask);


#ifdef __cplusplus
}
#endif

#endif // __ADS1x1x_H__
