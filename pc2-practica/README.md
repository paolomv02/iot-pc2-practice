# Moen Cia Steel Faucet with MotionSense Wave™ Technology

## Project Overview

This project implements a smart water faucet for Moen Inc., featuring touchless operation using ultrasonic proximity detection. The device automatically controls water flow when hands are detected within a 10cm threshold, providing a hygienic and efficient water usage solution.

## Features

- **MotionSense Wave™ Technology**: Touchless proximity detection using ultrasonic sensor
- **Automatic Water Control**: 5-second timed water flow activation
- **Smart Water Network**: WiFi connectivity for remote monitoring and configuration
- **Visual Feedback**: Blue LED status indication
- **Efficient Operation**: 1.2 GPM (4.5L/min) maximum flow rate at 60 PSI
- **Real-time Monitoring**: Console output every 2.5 seconds with device status

## Hardware Requirements

- ESP32 microcontroller
- HC-SR04 Ultrasonic Distance Sensor
- Relay Module (for water valve control)
- Blue LED (built-in ESP32 LED on GPIO 2)
- Water valve compatible with relay control

## Pin Configuration

| Component | ESP32 Pin | Description |
|-----------|-----------|-------------|
| Ultrasound Trigger | GPIO 5 | Trigger pin for distance measurement |
| Ultrasound Echo | GPIO 18 | Echo pin for distance measurement |
| Relay Control | GPIO 19 | Controls water valve relay |
| Status LED | GPIO 2 | Built-in blue LED for status indication |

## Software Architecture

The project uses the **Modest IoT Nano-framework** with object-oriented design principles:

### Core Classes

1. **UltrasoundSensor**: Handles proximity detection and event generation
2. **RelayModule**: Controls water valve with timed operations
3. **Led**: Manages status LED indication
4. **CiaSteelFaucet**: Main device class integrating all components

### Design Patterns

- **Event-Driven Architecture**: Sensors generate events, actuators respond to commands
- **CQRS-Inspired**: Separation of event handling and command processing
- **Observer Pattern**: Event propagation through handler chains

## Installation and Setup

1. **Hardware Setup**:
   - Connect HC-SR04 sensor to GPIO 5 (Trig) and GPIO 18 (Echo)
   - Connect relay module to GPIO 19
   - Ensure proper power supply for all components

2. **Software Configuration**:
   ```cpp
   // Update WiFi credentials in sketch.ino
   #define WIFI_SSID "YourWiFiNetwork"
   #define WIFI_PASSWORD "YourPassword"
   ```

3. **Upload Code**:
   - Use Arduino IDE or PlatformIO
   - Select ESP32 board configuration
   - Upload the sketch to your ESP32

## Operation

1. **Power On**: Device initializes and displays welcome message
2. **WiFi Connection**: Attempts to connect to configured network
3. **Active Mode**: Blue LED turns on, proximity monitoring begins
4. **Proximity Detection**: When hands approach within 10cm:
   - LED confirms detection
   - Water valve opens for 5 seconds
   - Console logs the event
5. **Status Updates**: Device reports status every 2.5 seconds

## Console Output Example

```
=====================================
        MOEN, INC.
   Cia Steel Faucet with
   MotionSense Wave™ Technology
=====================================

Innovating water solutions since 1937
Smart Water Network Technology
Maximum Flow: 1.2 GPM (4.5L/min) @ 60 PSI

Developer: [Your Name]
Team: Moen Inc. Development Team
Version: 1.0
Date: June 27, 2025

--- Moen Cia Steel Faucet Status ---
Proximity: 15.2 cm
Water Valve: closed
Status LED: ON
WiFi: Connected to MyNetwork (IP: 192.168.1.100)
------------------------------------
```

## Smart Water Network Integration

The device supports WiFi connectivity for integration with the Moen Smart Water Network, enabling:

- Remote monitoring of water usage
- Threshold configuration via mobile app
- Device status reporting
- Firmware updates

## Technical Specifications

- **Proximity Range**: 2-400 cm (effective range)
- **Detection Threshold**: 10 cm (configurable)
- **Water Flow Duration**: 5 seconds
- **Status Update Frequency**: 2.5 seconds
- **Maximum Flow Rate**: 1.2 GPM (4.5 L/min)
- **Operating Pressure**: 60 PSI
- **WiFi**: 802.11 b/g/n (2.4 GHz)

## File Structure

```
project/
├── sketch.ino              # Main Arduino sketch
├── ModestIoT.h            # Framework header (includes all components)
├── CiaSteelFaucet.h/cpp   # Main device implementation
├── UltrasoundSensor.h/cpp # Proximity sensor class
├── RelayModule.h/cpp      # Water valve control class
├── Led.h/cpp              # LED actuator class
├── Device.h/cpp           # Abstract device base class
├── Sensor.h/cpp           # Abstract sensor base class
├── Actuator.h/cpp         # Abstract actuator base class
├── EventHandler.h         # Event handling interface
├── CommandHandler.h       # Command handling interface
└── Button.h/cpp           # Button sensor (framework component)
```

## Development Team

**Moen Inc. Development Team**
- Developer: [Your Name]
- Framework: Modest IoT Nano-framework (C++ Edition)
- Date: June 27, 2025
- Version: 1.0

## License

This project is developed for Moen Inc. using the Modest IoT Nano-framework (C++ Edition) by Angel Velasquez.

---

*Moen: Innovating water solutions since 1937*
