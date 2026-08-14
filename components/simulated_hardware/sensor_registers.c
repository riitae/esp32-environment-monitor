#include "sensor_registers.h"

static uint8_t sensor_registers[256];

void simulated_sensor_init(void)
{
    sensor_registers[REG_DEVICE_ID] = 0x60;

    sensor_registers[REG_TEMPERATURE_MSB] = 0x00;
    sensor_registers[REG_TEMPERATURE_LSB] = 245;

    sensor_registers[REG_HUMIDITY_MSB] = 0x01;
    sensor_registers[REG_HUMIDITY_LSB] = 244;
}

uint8_t simulated_sensor_read_register(uint8_t reg)
{
    return sensor_registers[reg];
}

void simulated_sensor_write_register(uint8_t reg, uint8_t value)
{
    sensor_registers[reg] = value;
}