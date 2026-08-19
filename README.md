# ESP32 Environmental Monitor

An environmental monitoring project for the ESP32-S3, developed using ESP-IDF and C.

The project uses a simulated environmental sensor to produce temperature and humidity readings. The sensor is accessed through a simulated I²C interface. The ESP32 application also includes Wi-Fi and MQTT communication.

The project includes a separate sensor test that can be run without physical hardware.

## Features

* ESP32-S3 application developed with ESP-IDF
* C and FreeRTOS
* Separate components for the sensor, I²C, Wi-Fi, and MQTT
* Simulated I²C register communication
* Simulated environmental sensor
* Temperature and humidity readings
* Basic sensor initialization and validation
* Wi-Fi connection and reconnection
* MQTT connection and publishing
* Basic error handling
* Periodic sensor readings
* Sensor testing without physical hardware

## Project Architecture

```text
Application
    │
    ├── Environmental Sensor
    │       │
    │       └── I²C
    │              │
    │              └── Simulated Sensor
    │
    ├── Wi-Fi Manager
    │
    └── MQTT Manager
```

The application reads temperature and humidity regularly, prints the readings, and sends them through MQTT.

## Project Structure 

```text
esp32-environment-monitor/
├── components/
│   ├── i2c/
│   │   ├── i2c.c
│   │   ├── i2c.h
│   │   └── CMakeLists.txt
│   │
│   ├── sensors/
│   │   ├── environmental_sensor.c
│   │   ├── environmental_sensor.h
│   │   └── CMakeLists.txt
│   │
│   ├── simulated_hardware/
│   │   ├── sensor_registers.c
│   │   ├── sensor_registers.h
│   │   └── CMakeLists.txt
│   │
│   ├── wifi/
│   │   ├── wifi_manager.c
│   │   ├── wifi_manager.h
│   │   └── CMakeLists.txt
│   │
│   └── mqtt_manager/
│       ├── mqtt_manager.c
│       ├── mqtt_manager.h
│       └── CMakeLists.txt
│
├── main/
│   ├── esp32-environment-monitor.c
│   ├── CMakeLists.txt
│   ├── Kconfig.projbuild
│   └── idf_component.yml
│
├── tests/
│   └── test_environmental_sensor.c
│
├── CMakeLists.txt
└── dependencies.lock

## Components

### Simulated Sensor

`components/simulated_hardware/`

The simulated sensor uses a 256-byte array to represent sensor registers.

The registers include:

* Device ID
* Temperature MSB
* Temperature LSB
* Humidity MSB
* Humidity LSB

The temperature and humidity values change gradually to simulate changing environmental conditions.

### I²C

`components/i2c/`

This component provides the functions used by the environmental sensor to read and write sensor registers.

For this project, the I²C layer is simulated. Instead of communicating with a physical environmental sensor, the I²C functions access the simulated sensor registers.

This allows the sensor driver logic to be developed and tested without physical hardware.

### Environmental Sensor

`components/sensors/`

The environmental sensor component:

1. Initializes the I²C interface.
2. Reads the sensor device ID.
3. Checks that the device ID is correct.
4. Reads the temperature and humidity registers.
5. Combines the register values.
6. Converts the values into °C and %.
7. Checks that the readings are within the expected range.

### Wi-Fi Manager

`components/wifi/`

The Wi-Fi manager:

* Configures the ESP32 in station mode.
* Starts Wi-Fi.
* Connects to the configured network.
* Detects when an IP address is received.
* Tries to reconnect if Wi-Fi is disconnected.
* Allows the application to wait for Wi-Fi before starting MQTT.

### MQTT Manager

`components/mqtt_manager/`

The MQTT manager:

* Initializes the MQTT client.
* Connects to the MQTT broker.
* Keeps track of the MQTT connection.
* Publishes temperature and humidity.
* Checks whether publishing was successful.

The readings are published to:

```text
environment/temperature
environment/humidity
```

## Application Flow

The application starts in this order:

```text
ESP32 startup
      │
      ▼
Initialize environmental sensor
      │
      ▼
Start Wi-Fi
      │
      ▼
Wait for Wi-Fi connection
      │
      ▼
Start MQTT
      │
      ▼
Start sensor monitoring
      │
      ▼
Read temperature and humidity
      │
      ├── Print readings
      │
      └── Send readings through MQTT
      │
      ▼
Repeat every 2 seconds
```

This makes sure that MQTT is not started before the network connection is ready.

## Sensor Testing

The project includes a separate sensor test:

`tests/test_environmental_sensor.c`

The test uses the simulated sensor, so a physical ESP32 or environmental sensor is not needed to run it.

The compiled `tests/sensor_test` executable is only created locally and is excluded using `.gitignore`.

### Build the sensor test

From the project folder:

```bash
cc \
tests/test_environmental_sensor.c \
components/sensors/environmental_sensor.c \
components/i2c/i2c.c \
components/simulated_hardware/sensor_registers.c \
-Icomponents/sensors \
-Icomponents/i2c \
-Icomponents/simulated_hardware \
-o tests/sensor_test
```

### Run the test

```bash
./tests/sensor_test
```

A successful test initializes the sensor and reads several temperature and humidity values.

Example output:

```text
PASS: Sensor initialized successfully

Reading  1 | Temperature:  23.6 C | Humidity:  48.1 %
Reading  2 | Temperature:  23.7 C | Humidity:  48.2 %
Reading  3 | Temperature:  23.8 C | Humidity:  48.3 %
Reading  4 | Temperature:  23.9 C | Humidity:  48.4 %
Reading  5 | Temperature:  24.0 C | Humidity:  48.5 %
Reading  6 | Temperature:  24.1 C | Humidity:  48.6 %
Reading  7 | Temperature:  24.2 C | Humidity:  48.7 %
Reading  8 | Temperature:  24.3 C | Humidity:  48.8 %
Reading  9 | Temperature:  24.4 C | Humidity:  48.9 %
Reading 10 | Temperature:  24.5 C | Humidity:  49.0 %

PASS: All sensor readings are valid

```

The `tests/sensor_test` file is created when the test is compiled. It is only a local test program and should not be committed to GitHub.


## Building the ESP32 Application

This project uses ESP-IDF.

After ESP-IDF is configured, run:

```bash
idf.py build
```

A successful build ends with:

```text
Project build complete.
```

## Configuration

Wi-Fi and MQTT settings are configured through ESP-IDF.

The project uses configuration values such as:

```text
CONFIG_WIFI_SSID
CONFIG_WIFI_PASSWORD
CONFIG_MQTT_BROKER_URI
```

Do not put your real Wi-Fi password or other private information in the GitHub repository.

Configure these values locally using the ESP-IDF configuration system.


## Running on the ESP32

The project is designed to run on an ESP32-S3 board.

After configuring the Wi-Fi and MQTT settings and connecting an ESP32-S3, the application can be flashed using:

```bash
idf.py flash
```

or:

```bash
idf.py -p PORT flash
```

To build, flash, and view the serial output:

```bash
idf.py flash monitor
```

The physical ESP32-S3 runtime was not tested during development because a board was not available. The sensor functionality was tested separately using the simulated hardware layer.


## Expected Application Output

The ESP32 application includes messages for sensor initialization, Wi-Fi, and MQTT.

Since this project was developed without a physical ESP32-S3 board, the complete hardware runtime has not been tested.

The application is designed to produce messages similar to:

```text
Environmental sensor initialized successfully
Wi-Fi initialization complete
Connected. IP address: <device IP>
MQTT initialization complete
MQTT connected
```

The standalone sensor test has been tested successfully using the simulated sensor.


## Error Handling and Recovery

The project includes basic error handling for the sensor, Wi-Fi, and MQTT.

### Sensor

* Detects sensor initialization failure
* Tries to initialize the sensor again
* Detects I²C read failures
* Rejects invalid environmental values

### Wi-Fi

* Automatically tries to connect when Wi-Fi starts
* Tries to reconnect after disconnection
* Reports the IP address after connecting

### MQTT

* Keeps track of the MQTT connection
* Does not publish while disconnected
* Checks MQTT publish results
* Reports MQTT errors

The goal is to detect problems and keep the application running when possible.

## Technologies

* C
* ESP32-S3
* ESP-IDF
* FreeRTOS
* I²C
* Wi-Fi
* MQTT
* CMake
* Git

## Project Status

This is my first embedded-systems project. It focuses on learning and implementing the main parts of a small environmental monitoring application.

The project includes:

* Sensor register simulation
* Simulated I²C communication
* Environmental sensor driver
* FreeRTOS task
* Wi-Fi connection
* MQTT communication
* Error handling
* Sensor testing
* Separate project components

The simulated sensor makes it possible to develop and test the sensor-related code without needing a physical environmental sensor.

The project also includes Wi-Fi and MQTT support for the full application.
