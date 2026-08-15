#include <stdio.h>
#include <assert.h>

#include "environmental_sensor.h"

int main(void)
{
    environmental_data_t data;

    printf("Initializing environmental sensor...\n");

    assert(environmental_sensor_init() == 0);

    printf("Sensor initialized successfully.\n");

    assert(environmental_sensor_read(&data) == 0);

    printf("Temperature: %.1f C\n", data.temperature);
    printf("Humidity: %.1f %%\n", data.humidity);

    assert(data.temperature == 24.5f);
    assert(data.humidity == 50.0f);

    printf("All sensor tests passed!\n");

    return 0;
}