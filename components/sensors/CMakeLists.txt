idf_component_register(
    SRCS "environmental_sensor.c"
    INCLUDE_DIRS "."
    REQUIRES i2c simulated_hardware
)