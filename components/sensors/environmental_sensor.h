#ifndef ENVIRONMENTAL_SENSOR_H
#define ENVIRONMENTAL_SENSOR_H

#include <stdint.h>

typedef struct
{
    float temperature;
    float humidity;
} environmental_data_t;

int environmental_sensor_init(void);

int environmental_sensor_read(environmental_data_t *data);

#endif