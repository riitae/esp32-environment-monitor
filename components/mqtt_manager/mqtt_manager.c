#include "mqtt_manager.h"

#include <stdio.h>

#include "mqtt_client.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "mqtt_manager";

static esp_mqtt_client_handle_t mqtt_client;

static void mqtt_event_handler(
    void *handler_args,
    esp_event_base_t base,
    int32_t event_id,
    void *event_data)
{
    switch ((esp_mqtt_event_id_t)event_id)
    {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT connected");
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT disconnected");
            break;

        case MQTT_EVENT_ERROR:
            ESP_LOGE(TAG, "MQTT error");
            break;

        default:
            break;
    }
}

void mqtt_manager_init(void)
{
    const esp_mqtt_client_config_t mqtt_config = {
        .broker.address.uri = CONFIG_MQTT_BROKER_URI,
    };

    mqtt_client = esp_mqtt_client_init(&mqtt_config);

    ESP_ERROR_CHECK(
        esp_mqtt_client_register_event(
            mqtt_client,
            ESP_EVENT_ANY_ID,
            mqtt_event_handler,
            NULL
        )
    );

    ESP_ERROR_CHECK(
        esp_mqtt_client_start(mqtt_client)
    );

    ESP_LOGI(TAG, "MQTT initialization complete");
}

void mqtt_publish_environment(
    float temperature,
    float humidity)
{
    char temperature_message[32];
    char humidity_message[32];

    snprintf(
        temperature_message,
        sizeof(temperature_message),
        "%.1f",
        temperature
    );

    snprintf(
        humidity_message,
        sizeof(humidity_message),
        "%.1f",
        humidity
    );

    esp_mqtt_client_publish(
        mqtt_client,
        "environment/temperature",
        temperature_message,
        0,
        1,
        0
    );

    esp_mqtt_client_publish(
        mqtt_client,
        "environment/humidity",
        humidity_message,
        0,
        1,
        0
    );
}