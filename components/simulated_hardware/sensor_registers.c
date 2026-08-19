#include "sensor_registers.h"

static uint8_t sensor_registers[256];

static int counter = 0;
static int temperature = 245;
static int humidity = 500;

static void simulated_sensor_update(void)
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

void simulated_sensor_init(void)
{
    counter = 0;

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
    if (reg == REG_TEMPERATURE_MSB)
    {
        simulated_sensor_update();
    }

    return sensor_registers[reg];
}

void simulated_sensor_write_register(uint8_t reg, uint8_t value)
{
    sensor_registers[reg] = value;
}