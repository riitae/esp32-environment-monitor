#include "sensor_registers.h"

static uint8_t sensor_registers[256];

static int counter = 0;
static int temperature = 245;
static int humidity = 500;

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
    /*
     * Update the simulated sensor once per complete
     * environmental reading.
     *
     * The temperature MSB is the first register read,
     * so we update the sensor values only at that point.
     * The following three register reads use the same values.
     */
    if (reg == REG_TEMPERATURE_MSB)
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