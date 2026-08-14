#ifndef SENSOR_REGISTERS_H
#define SENSOR_REGISTERS_H

#include <stdint.h>

#define SENSOR_DEVICE_ADDRESS 0x76

#define REG_DEVICE_ID          0x00
#define REG_TEMPERATURE_MSB    0x01
#define REG_TEMPERATURE_LSB    0x02
#define REG_HUMIDITY_MSB       0x03
#define REG_HUMIDITY_LSB       0x04

void simulated_sensor_init(void);

uint8_t simulated_sensor_read_register(uint8_t reg);

void simulated_sensor_write_register(uint8_t reg, uint8_t value);

#endif