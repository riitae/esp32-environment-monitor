#include "environmental_sensor.h"
#include "i2c.h"
#include "sensor_registers.h"

int environmental_sensor_init(void)
{
    i2c_init();

    uint8_t device_id = 0;

    if (i2c_read_register(
            SENSOR_DEVICE_ADDRESS,
            REG_DEVICE_ID,
            &device_id) != 0)
    {
        return -1;
    }

    if (device_id != 0x60)
    {
        return -1;
    }

    return 0;
}

int environmental_sensor_read(environmental_data_t *data)
{
    if (data == NULL)
    {
        return -1;
    }

    uint8_t temperature_msb;
    uint8_t temperature_lsb;
    uint8_t humidity_msb;
    uint8_t humidity_lsb;

    if (i2c_read_register(
            SENSOR_DEVICE_ADDRESS,
            REG_TEMPERATURE_MSB,
            &temperature_msb) != 0)
    {
        return -1;
    }

    if (i2c_read_register(
            SENSOR_DEVICE_ADDRESS,
            REG_TEMPERATURE_LSB,
            &temperature_lsb) != 0)
    {
        return -1;
    }

    if (i2c_read_register(
            SENSOR_DEVICE_ADDRESS,
            REG_HUMIDITY_MSB,
            &humidity_msb) != 0)
    {
        return -1;
    }

    if (i2c_read_register(
            SENSOR_DEVICE_ADDRESS,
            REG_HUMIDITY_LSB,
            &humidity_lsb) != 0)
    {
        return -1;
    }

    uint16_t temperature_raw =
        ((uint16_t)temperature_msb << 8) | temperature_lsb;

    uint16_t humidity_raw =
        ((uint16_t)humidity_msb << 8) | humidity_lsb;

    data->temperature = temperature_raw / 10.0f;
    data->humidity = humidity_raw / 10.0f;

    return 0;
}