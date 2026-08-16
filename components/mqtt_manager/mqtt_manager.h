#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <stdint.h>

void mqtt_manager_init(void);

void mqtt_publish_environment(
    float temperature,
    float humidity
);

#endif