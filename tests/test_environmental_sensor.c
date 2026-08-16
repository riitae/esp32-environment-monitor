#include <stdio.h>

#include "environmental_sensor.h"

int main(void)
{
    environmental_data_t data;

    printf("Initializing environmental sensor...\n");

    if (environmental_sensor_init() != 0)
    {
        printf("ERROR: Sensor initialization failed\n");
        return 1;
    }

    printf("Environmental sensor initialized successfully\n\n");

    for (int i = 0; i < 10; i++)
    {
        if (environmental_sensor_read(&data) == 0)
        {
            printf(
                "Reading %d: Temperature: %.1f C | Humidity: %.1f %%\n",
                i + 1,
                data.temperature,
                data.humidity
            );
        }
        else
        {
            printf("ERROR: Failed to read sensor\n");
        }
    }

    return 0;
}