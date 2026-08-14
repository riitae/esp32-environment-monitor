#include "i2c.h"
#include "sensor_registers.h"

void i2c_init(void)
{
    simulated_sensor_init();
}

int i2c_write_register(uint8_t device_address,
                       uint8_t reg,
                       uint8_t value)
{
    if (device_address != SENSOR_DEVICE_ADDRESS)
    {
        return -1;
    }

    simulated_sensor_write_register(reg, value);

    return 0;
}

int i2c_read_register(uint8_t device_address,
                      uint8_t reg,
                      uint8_t *value)
{
    if (device_address != SENSOR_DEVICE_ADDRESS || value == NULL)
    {
        return -1;
    }

    *value = simulated_sensor_read_register(reg);

    return 0;
}