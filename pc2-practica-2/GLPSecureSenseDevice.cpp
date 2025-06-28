#include "GLPSecureSenseDevice.h"
#include <Arduino.h>

GLPSecureSenseDevice::GLPSecureSenseDevice() : lastSerialOutput(0)
{
    gasSensor = new GasSensor(GAS_ANALOG_PIN, GAS_DIGITAL_PIN);
    ledIndicator = new LedIndicator(GREEN_LED_PIN, YELLOW_LED_PIN, RED_LED_PIN);
    displayManager = new DisplayManager(LCD_ADDRESS);
}

GLPSecureSenseDevice::~GLPSecureSenseDevice()
{
    delete gasSensor;
    delete ledIndicator;
    delete displayManager;
}

void GLPSecureSenseDevice::initialize()
{
    initializeSerial();

    Serial.println("=== GLP SecureSense Pro Initialization ===");
    Serial.println("Protech Innovations, Inc.");
    Serial.println("Initializing components...");

    // Initialize display and show startup message
    displayManager->initialize();
    displayManager->showStartupMessage();

    // Initialize LEDs
    ledIndicator->initialize();

    // Initialize gas sensor
    gasSensor->initialize();

    // Perform system test
    performSystemTest();

    // Calibrate sensor
    calibrateSensor();

    Serial.println("System ready for operation!");
}

void GLPSecureSenseDevice::run()
{
    updateSensorReadings();
    updateDisplay();
    updateLEDs();
    sendSerialData();
}

void GLPSecureSenseDevice::initializeSerial()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ; // Wait for serial port to connect
    }
}

void GLPSecureSenseDevice::calibrateSensor()
{
    displayManager->clear();
    displayManager->showCalibrationStatus(0.0);

    gasSensor->calibrate();

    Serial.println("Sensor calibration completed successfully!");
    delay(1000);
}

void GLPSecureSenseDevice::performSystemTest()
{
    Serial.println("Performing system test...");

    displayManager->clear();
    displayManager->showStartupMessage();

    // Test LED sequence
    ledIndicator->testSequence();

    Serial.println("System test completed!");
}

void GLPSecureSenseDevice::updateSensorReadings()
{
    gasSensor->update();
}

void GLPSecureSenseDevice::updateDisplay()
{
    float ppm = gasSensor->readPPM();
    int percentage = gasSensor->readPercentage();
    GasLevel level = gasSensor->getGasLevel();
    String status = gasSensor->getStatusText();

    displayManager->updateDisplay(ppm, percentage, level, status);
}

void GLPSecureSenseDevice::updateLEDs()
{
    GasLevel level = gasSensor->getGasLevel();
    ledIndicator->updateStatus(level);
}

void GLPSecureSenseDevice::sendSerialData()
{
    unsigned long currentTime = millis();
    if (currentTime - lastSerialOutput < SERIAL_INTERVAL)
    {
        return;
    }

    float ppm = gasSensor->readPPM();
    int percentage = gasSensor->readPercentage();
    GasLevel level = gasSensor->getGasLevel();

    logSensorData(ppm, percentage, level);

    lastSerialOutput = currentTime;
}

void GLPSecureSenseDevice::logSensorData(float ppm, int percentage, GasLevel level)
{
    Serial.println("=== GLP SecureSense Pro Reading ===");
    Serial.print("LPG Concentration: ");
    Serial.print(ppm);
    Serial.println(" PPM");

    Serial.print("Gas Level: ");
    Serial.print(percentage);
    Serial.println("%");

    Serial.print("Safety Level: ");
    switch (level)
    {
    case GasLevel::SAFE:
        Serial.println("SAFE (< 200 PPM)");
        break;
    case GasLevel::MODERATE:
        Serial.println("MODERATE (200-500 PPM)");
        break;
    case GasLevel::CRITICAL:
        Serial.println("CRITICAL (> 500 PPM) - EXPLOSION RISK!");
        break;
    }

    Serial.print("Digital Threshold: ");
    Serial.println(gasSensor->isDigitalHigh() ? "HIGH" : "LOW");
    Serial.println("=====================================");
}
