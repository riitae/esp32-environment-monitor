#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "environmental_sensor.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"

static void sensor_monitor_task(void *pvParameters)
{
    environmental_data_t data;

    while (1)
    {
        if (environmental_sensor_read(&data) == 0)
        {
            printf(
                "Temperature: %.1f C | Humidity: %.1f %%\n",
                data.temperature,
                data.humidity
            );

            if (mqtt_publish_environment(
                    data.temperature,
                    data.humidity) != 0)
            {
                printf(
                    "WARNING: Failed to publish environmental data\n"
                );
            }
        }
        else
        {
            printf(
                "ERROR: Failed to read environmental sensor\n"
            );
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

static void initialize_sensor(void)
{
    while (environmental_sensor_init() != 0)
    {
        printf(
            "ERROR: Environmental sensor initialization failed\n"
        );

        printf(
            "Sensor unavailable. Retrying in 5 seconds...\n"
        );

        vTaskDelay(pdMS_TO_TICKS(5000));
    }

    printf(
        "Environmental sensor initialized successfully\n"
    );
}

void app_main(void)
{
    initialize_sensor();

    wifi_manager_init();

    if (wifi_manager_wait_for_connection() != 0)
    {
        printf("ERROR: Wi-Fi connection failed\n");
        return;
    }

    mqtt_manager_init();

    if (xTaskCreate(
            sensor_monitor_task,
            "sensor_monitor",
            4096,
            NULL,
            5,
            NULL) != pdPASS)
    {
        printf("ERROR: Failed to create sensor monitor task\n");
        return;
    }
}