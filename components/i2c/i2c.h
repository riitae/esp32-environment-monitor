#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stddef.h>

void i2c_init(void);

int i2c_write_register(uint8_t device_address,
                       uint8_t reg,
                       uint8_t value);

int i2c_read_register(uint8_t device_address,
                      uint8_t reg,
                      uint8_t *value);

#endif