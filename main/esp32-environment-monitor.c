#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "environmental_sensor.h"
#include "wifi_manager.h"

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
            printf("ERROR: Failed to read environmental sensor\n");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    if (environmental_sensor_init() != 0)
    {
        printf("ERROR: Environmental sensor initialization failed\n");

        while (1)
        {
            printf("Sensor unavailable. Retrying in 5 seconds...\n");
            vTaskDelay(pdMS_TO_TICKS(5000));

            if (environmental_sensor_init() == 0)
            {
                printf("Environmental sensor initialized successfully\n");
                break;
            }
        }
    }
    else
    {
        printf("Environmental sensor initialized successfully\n");
    }

    wifi_manager_init();

    xTaskCreate(
        sensor_monitor_task,
        "sensor_monitor",
        4096,
        NULL,
        5,
        NULL
    );
}