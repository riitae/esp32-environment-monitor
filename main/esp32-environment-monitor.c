#include <stdio.h>
#include "environmental_sensor.h"

void app_main(void)
{
    environmental_data_t data;

    if (environmental_sensor_init() != 0)
    {
        printf("Sensor initialization failed\n");
        return;
    }

    printf("Environmental sensor initialized successfully\n");

    if (environmental_sensor_read(&data) != 0)
    {
        printf("Failed to read environmental data\n");
        return;
    }

    printf("Temperature: %.1f C\n", data.temperature);
    printf("Humidity: %.1f %%\n", data.humidity);
}
