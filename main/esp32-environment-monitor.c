#include <stdio.h>
#include <assert.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "environmental_sensor.h"

static void test_environmental_sensor(void)
{
    environmental_data_t data;

    printf("\n=== Environmental Sensor Test ===\n");

    assert(environmental_sensor_init() == 0);

    printf("Sensor initialized successfully.\n");

    assert(environmental_sensor_read(&data) == 0);

    printf("Temperature: %.1f C\n", data.temperature);
    printf("Humidity: %.1f %%\n", data.humidity);

    assert(data.temperature == 24.5f);
    assert(data.humidity == 50.0f);

    printf("All sensor tests passed!\n");
}

static void sensor_monitor_task(void *pvParameters)
{
    environmental_data_t data;

    while (1)
    {
        if (environmental_sensor_read(&data) == 0)
        {
            printf("Temperature: %.1f C | Humidity: %.1f %%\n",
                   data.temperature,
                   data.humidity);
        }
        else
        {
            printf("Failed to read environmental data\n");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    test_environmental_sensor();

    xTaskCreate(
        sensor_monitor_task,
        "sensor_monitor",
        4096,
        NULL,
        5,
        NULL
    );
}