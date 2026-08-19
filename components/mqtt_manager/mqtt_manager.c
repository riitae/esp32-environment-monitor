#include "mqtt_manager.h"

#include <stdbool.h>
#include <stdio.h>

#include "mqtt_client.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "mqtt_manager";

static esp_mqtt_client_handle_t mqtt_client;
static bool mqtt_connected = false;

static void mqtt_event_handler(
    void *handler_args,
    esp_event_base_t base,
    int32_t event_id,
    void *event_data)
{
    switch ((esp_mqtt_event_id_t)event_id)
    {
        case MQTT_EVENT_CONNECTED:
            mqtt_connected = true;
            ESP_LOGI(TAG, "MQTT connected");
            break;

        case MQTT_EVENT_DISCONNECTED:
            mqtt_connected = false;
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

if (mqtt_client == NULL)
{
    ESP_LOGE(TAG, "Failed to initialize MQTT client");
    return;
}

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

int mqtt_publish_environment(
    float temperature,
    float humidity)
{
    if (!mqtt_connected)
    {
        ESP_LOGW(
            TAG,
            "MQTT not connected. Skipping publish."
        );

        return -1;
    }

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

    int temperature_result = esp_mqtt_client_publish(
        mqtt_client,
        "environment/temperature",
        temperature_message,
        0,
        1,
        0
    );

    int humidity_result = esp_mqtt_client_publish(
        mqtt_client,
        "environment/humidity",
        humidity_message,
        0,
        1,
        0
    );

    if (temperature_result < 0 || humidity_result < 0)
    {
        ESP_LOGE(
            TAG,
            "Failed to publish environmental data"
        );

        return -1;
    }

    return 0;
}