#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "environmental_sensor.h"

static void sensor_monitor_task(void *pvParameters)
{
    environmental_data_t data;

    while (1)
    {
        if (environmental_sensor_read(&data) == 0)
        {
            printf("Temperature: %.1f C\n", data.temperature);
            printf("Humidity: %.1f %%\n", data.humidity);
        }
        else
        {
            printf("Failed to read environmental data\n");
        }

        printf("-----------------------------\n");

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    if (environmental_sensor_init() != 0)
    {
        printf("Sensor initialization failed\n");
        return;
    }

    printf("Environmental sensor initialized successfully\n");

    xTaskCreate(
        sensor_monitor_task,
        "sensor_monitor",
        4096,
        NULL,
        5,
        NULL
    );
}