#ifndef CIA_STEEL_FAUCET_H
#define CIA_STEEL_FAUCET_H

/**
 * @file CiaSteelFaucet.h
 * @brief Declares the CiaSteelFaucet device class.
 *
 * Main device class for the Moen Cia Steel Faucet with MotionSense Wave™ technology.
 * Integrates ultrasound proximity sensing, LED indication, and relay-controlled water valve
 * for touchless operation with Smart Water Network connectivity.
 *
 * @author Your Name - Moen Inc. Development Team
 * @date June 27, 2025
 * @version 1.0
 */

/*
 * This file is part of the Moen Cia Steel Faucet project.
 * Developed using the Modest IoT Nano-framework (C++ Edition).
 */

#include "Device.h"
#include "UltrasoundSensor.h"
#include "RelayModule.h"
#include "Led.h"
#include <WiFi.h>

class CiaSteelFaucet : public Device
{
private:
    UltrasoundSensor proximitydetector; ///< Ultrasound sensor for proximity detection
    RelayModule waterValve;             ///< Relay module for water valve control
    Led statusLed;                      ///< Blue LED for device status indication

    unsigned long lastStatusUpdate;     ///< Last time status was printed to console
    unsigned long statusUpdateInterval; ///< Interval for status updates (2.5 seconds)

    // WiFi configuration
    const char *ssid;
    const char *password;
    bool wifiConnected;

public:
    // Pin definitions for ESP32
    static const int ULTRASOUND_TRIG_PIN = 5;  ///< Trigger pin for ultrasound sensor
    static const int ULTRASOUND_ECHO_PIN = 18; ///< Echo pin for ultrasound sensor
    static const int RELAY_PIN = 19;           ///< Relay control pin
    static const int LED_PIN = 2;              ///< Built-in LED pin (blue)

    // Configuration constants
    static const int PROXIMITY_THRESHOLD_CM = 10;                ///< 10cm proximity threshold
    static const unsigned long VALVE_OPEN_DURATION_MS = 5000;    ///< 5 seconds valve open time
    static const unsigned long STATUS_UPDATE_INTERVAL_MS = 2500; ///< 2.5 seconds status update

    /**
     * @brief Constructs a CiaSteelFaucet device.
     * @param wifiSSID WiFi network name (optional for offline operation).
     * @param wifiPassword WiFi network password (optional for offline operation).
     */
    CiaSteelFaucet(const char *wifiSSID = nullptr, const char *wifiPassword = nullptr);

    /**
     * @brief Initializes the device and all components.
     * Should be called in Arduino setup() function.
     */
    void initialize();

    /**
     * @brief Main update loop for the device.
     * Should be called in Arduino loop() function.
     */
    void update();

    /**
     * @brief Handles events from sensors (proximity detection).
     * @param event The event to process.
     */
    void on(Event event) override;

    /**
     * @brief Handles commands issued to the device.
     * @param command The command to execute.
     */
    void handle(Command command) override;

    /**
     * @brief Prints device and company information to console.
     */
    void printWelcomeMessage();

    /**
     * @brief Prints current device status to console.
     */
    void printStatus();

    /**
     * @brief Initializes WiFi connection.
     */
    void initializeWiFi();

    /**
     * @brief Gets the proximity sensor reference.
     * @return Reference to the ultrasound sensor.
     */
    UltrasoundSensor &getProximitydetector();

    /**
     * @brief Gets the water valve reference.
     * @return Reference to the relay module.
     */
    RelayModule &getWaterValve();

    /**
     * @brief Gets the status LED reference.
     * @return Reference to the LED.
     */
    Led &getStatusLed();

    /**
     * @brief Checks if WiFi is connected.
     * @return True if WiFi is connected, false otherwise.
     */
    bool isWiFiConnected() const;
};

#endif // CIA_STEEL_FAUCET_H
