#include <stdio.h>

#include "environmental_sensor.h"

int main(void)
{
    environmental_data_t data;

    float previous_temperature = 0.0f;
    float previous_humidity = 0.0f;

    printf("=== Environmental Sensor Test ===\n\n");

    if (environmental_sensor_init() != 0)
    {
        printf("FAIL: Sensor initialization failed\n");
        return 1;
    }

    printf("PASS: Sensor initialized successfully\n\n");

    for (int i = 0; i < 10; i++)
    {
        if (environmental_sensor_read(&data) != 0)
        {
            printf("FAIL: Reading %d failed\n", i + 1);
            return 1;
        }

        printf(
            "Reading %2d | Temperature: %5.1f C | Humidity: %5.1f %%\n",
            i + 1,
            data.temperature,
            data.humidity
        );

        if (data.temperature < 20.0f || data.temperature > 30.0f)
        {
            printf("FAIL: Temperature out of expected range\n");
            return 1;
        }

        if (data.humidity < 40.0f || data.humidity > 60.0f)
        {
            printf("FAIL: Humidity out of expected range\n");
            return 1;
        }

        if (i > 0 &&
            data.temperature == previous_temperature &&
            data.humidity == previous_humidity)
        {
            printf("FAIL: Sensor readings are not changing\n");
            return 1;
        }

        previous_temperature = data.temperature;
        previous_humidity = data.humidity;
    }

    printf("\nPASS: All sensor readings are valid\n");
    return 0;
}