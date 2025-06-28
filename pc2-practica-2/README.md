# GLP SecureSense Pro - IoT Gas Detection System

## Company Overview
**Protech Innovations, Inc.** - Founded in 2012, specializing in industrial and residential security solutions. Our mission is to protect people and property through early risk detection devices, leveraging IoT technologies to create safe and monitored environments in real-time.

## Product Description
The **GLP SecureSense Pro** is an advanced IoT-enabled device designed specifically for monitoring Liquefied Petroleum Gas (LPG) concentrations in enclosed or high-risk spaces. This enhanced version features improved sensor accuracy, comprehensive visual indicators, and an enhanced user interface.

## Features

### Enhanced Safety Monitoring System
The device implements a three-tier safety classification system based on LPG concentration levels:

| LPG Concentration (PPM) | Safety Level | LED Indicator | Risk Assessment |
|------------------------|--------------|---------------|-----------------|
| < 200 PPM | **SAFE** | 🟢 Green | Normal operation, no risk |
| 200-500 PPM | **MODERATE** | 🟡 Yellow | Caution required, ventilation recommended |
| > 500 PPM | **CRITICAL** | 🔴 Red | **EXPLOSION RISK** - Immediate evacuation required |

### System Components

#### Hardware Components
- **ESP32 DevKit V1**: Main microcontroller
- **MQ-2 Gas Sensor**: Custom chip for LPG detection
- **LCD 20x4 I2C Display**: Enhanced display with 4 rows and 20 columns
- **RGB LED Indicators**: Visual status indication system
  - Green LED (Pin 25): Safe status
  - Yellow LED (Pin 26): Moderate risk
  - Red LED (Pin 27): Critical risk

#### Software Architecture
The system implements **Object-Oriented Programming (OOP)** principles with the following classes:

1. **`GLPSecureSenseDevice`**: Main device controller
2. **`GasSensor`**: MQ-2 sensor management and calibration
3. **`LedIndicator`**: LED status management
4. **`DisplayManager`**: Enhanced LCD display control

### Enhanced Display Features
The new 20x4 LCD display provides comprehensive information:

```
=== GLP MONITOR ===
LPG: 245 PPM     12:34
Level: 67%
Status: [Y] MODERATE
```

**Display Information:**
- **Line 1**: System header with real-time timestamp
- **Line 2**: LPG concentration in PPM with percentage level
- **Line 3**: Gas level percentage
- **Line 4**: Safety status with color indicator and text

### Real-time Monitoring
- **Serial Logging**: Detailed sensor data every second
- **Visual Indicators**: Immediate LED status updates
- **Display Updates**: Refreshed every 500ms
- **Sensor Calibration**: Automatic R0 calibration on startup

## Technical Implementation

### Object-Oriented Design
The system follows OOP best practices:

- **Encapsulation**: Each component is wrapped in its own class
- **Abstraction**: Clean interfaces between components
- **Modularity**: Separate header and implementation files
- **Maintainability**: Easy to extend and modify

### Pin Configuration
```cpp
// Gas Sensor Pins
#define GAS_ANALOG_PIN    4   // MQ-2 Analog output
#define GAS_DIGITAL_PIN   23  // MQ-2 Digital output

// LED Indicator Pins
#define GREEN_LED_PIN     25  // Safe status
#define YELLOW_LED_PIN    26  // Moderate risk
#define RED_LED_PIN       27  // Critical risk

// I2C Display
#define LCD_ADDRESS       0x27
#define SDA_PIN           21
#define SCL_PIN           22
```

### Libraries Used
- **LiquidCrystal I2C**: Enhanced LCD control
- **MQUnifiedsensor**: Professional MQ-2 sensor library
- **Wire**: I2C communication

## System Operation

### Startup Sequence
1. **System Initialization**: Display startup message
2. **Component Testing**: LED sequence test
3. **Sensor Calibration**: Automatic R0 calibration (10 iterations)
4. **Operation Mode**: Continuous monitoring begins

### Monitoring Cycle
1. **Sensor Reading**: Update MQ-2 sensor values
2. **Data Processing**: Calculate PPM and percentage
3. **Safety Assessment**: Determine risk level
4. **Visual Updates**: Update LEDs and display
5. **Serial Logging**: Output detailed information

### Error Handling
- **Calibration Validation**: Prevents infinite or zero R0 values
- **Connection Monitoring**: Detects wiring issues
- **Safe Fallback**: System halts on critical errors

## Serial Output Example
```
=== GLP SecureSense Pro Reading ===
LPG Concentration: 245 PPM
Gas Level: 67%
Safety Level: MODERATE (200-500 PPM)
Digital Threshold: LOW
=====================================
```

## Installation & Usage

### Wokwi Simulation
1. Access the project: [Wokwi Simulation Link](https://wokwi.com/projects/412404352853061633)
2. The simulation includes all components pre-wired
3. Use the gas sensor controls to simulate different concentration levels
4. Observe the LED indicators and display updates

### Physical Implementation
1. Wire components according to the pin configuration
2. Upload the sketch to ESP32
3. Monitor serial output for debugging
4. Observe LED indicators for immediate status
5. Read detailed information on the LCD display

## Safety Guidelines

⚠️ **CRITICAL SAFETY WARNINGS**:
- **RED LED = IMMEDIATE DANGER**: Evacuate area immediately
- **Ventilation**: Ensure proper ventilation in monitoring areas
- **Regular Calibration**: Recalibrate sensor periodically
- **Professional Installation**: Use certified technicians for installation

## Future Enhancements
- **IoT Connectivity**: Cloud monitoring and mobile alerts
- **Data Logging**: Historical trend analysis
- **Multiple Sensors**: Multi-point monitoring capability
- **Wireless Communication**: Remote monitoring capabilities

---

**Protech Innovations, Inc.**  
*Protecting Lives Through Innovation*  
© 2024 - Professional IoT Security Solutions
