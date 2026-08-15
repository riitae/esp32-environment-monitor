idf_component_register(
    SRCS "esp32-environment-monitor.c"
    INCLUDE_DIRS "."
    REQUIRES sensors wifi
)