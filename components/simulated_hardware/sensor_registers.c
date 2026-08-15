#include "sensor_registers.h"

static uint8_t sensor_registers[256];

static int temperature = 245;
static int humidity = 500;

void simulated_sensor_init(void)
{
    sensor_registers[REG_DEVICE_ID] = 0x60;

    temperature = 245;
    humidity = 500;

    sensor_registers[REG_TEMPERATURE_MSB] =
        (temperature >> 8) & 0xFF;

    sensor_registers[REG_TEMPERATURE_LSB] =
        temperature & 0xFF;

    sensor_registers[REG_HUMIDITY_MSB] =
        (humidity >> 8) & 0xFF;

    sensor_registers[REG_HUMIDITY_LSB] =
        humidity & 0xFF;
}

uint8_t simulated_sensor_read_register(uint8_t reg)
{
    static int counter = 0;

    if (reg == REG_TEMPERATURE_MSB ||
        reg == REG_TEMPERATURE_LSB ||
        reg == REG_HUMIDITY_MSB ||
        reg == REG_HUMIDITY_LSB)
    {
        counter++;

        temperature = 245 + (counter % 20) - 10;
        humidity = 500 + (counter % 40) - 20;

        sensor_registers[REG_TEMPERATURE_MSB] =
            (temperature >> 8) & 0xFF;

        sensor_registers[REG_TEMPERATURE_LSB] =
            temperature & 0xFF;

        sensor_registers[REG_HUMIDITY_MSB] =
            (humidity >> 8) & 0xFF;

        sensor_registers[REG_HUMIDITY_LSB] =
            humidity & 0xFF;
    }

    return sensor_registers[reg];
}

void simulated_sensor_write_register(uint8_t reg, uint8_t value)
{
    sensor_registers[reg] = value;
}