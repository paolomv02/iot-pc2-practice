#ifndef GLP_SECURE_SENSE_DEVICE_H
#define GLP_SECURE_SENSE_DEVICE_H

#include "GasSensor.h"
#include "LedIndicator.h"
#include "DisplayManager.h"

class GLPSecureSenseDevice
{
private:
    GasSensor *gasSensor;
    LedIndicator *ledIndicator;
    DisplayManager *displayManager;

    // Pin definitions
    static const int GAS_ANALOG_PIN = 4;
    static const int GAS_DIGITAL_PIN = 23;
    static const int GREEN_LED_PIN = 25;
    static const int YELLOW_LED_PIN = 26;
    static const int RED_LED_PIN = 27;
    static const uint8_t LCD_ADDRESS = 0x27;

    unsigned long lastSerialOutput;
    static const unsigned long SERIAL_INTERVAL = 1000;

public:
    GLPSecureSenseDevice();
    ~GLPSecureSenseDevice();

    void initialize();
    void run();

private:
    void initializeSerial();
    void calibrateSensor();
    void performSystemTest();
    void updateSensorReadings();
    void updateDisplay();
    void updateLEDs();
    void sendSerialData();
    void logSensorData(float ppm, int percentage, GasLevel level);
};

#endif
