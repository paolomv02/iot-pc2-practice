/**
 * @file MoenCiaSteelFaucet.ino
 * @brief Main sketch for the Moen Cia Steel Faucet with MotionSense Wave™ Technology.
 *
 * Implements a touchless water faucet using the Modest IoT Nano-framework (C++ Edition).
 * Features ultrasonic proximity detection, automatic water valve control, LED status indication,
 * and WiFi connectivity for Smart Water Network integration.
 *
 * @author [Your Name] - Moen Inc. Development Team
 * @date June 27, 2025
 * @version 1.0
 */

/*
 * This file is part of the Moen Cia Steel Faucet project.
 * Developed using the Modest IoT Nano-framework (C++ Edition).
 *
 * Hardware Requirements:
 * - ESP32 microcontroller
 * - HC-SR04 Ultrasonic Distance Sensor
 * - Relay Module for water valve control
 * - Blue LED for status indication
 * - Water valve with 1.2 GPM max flow @ 60 PSI
 *
 * Pin Configuration:
 * - Ultrasound Trigger: GPIO 5
 * - Ultrasound Echo: GPIO 18
 * - Relay Control: GPIO 19
 * - Status LED: GPIO 2 (built-in)
 */

#include "ModestIoT.h"

// WiFi Configuration (optional - for Smart Water Network)
#define WIFI_SSID "YourWiFiNetwork"  ///< Replace with your WiFi network name
#define WIFI_PASSWORD "YourPassword" ///< Replace with your WiFi password

// Device instance
CiaSteelFaucet faucetDevice(WIFI_SSID, WIFI_PASSWORD);

/**
 * @brief Arduino setup function - initializes the Moen Cia Steel Faucet device.
 *
 * Configures all hardware components, establishes WiFi connection if available,
 * and prepares the MotionSense Wave™ technology for operation.
 */
void setup()
{
    // Initialize the Cia Steel Faucet device
    faucetDevice.initialize();
}

/**
 * @brief Arduino main loop - continuously monitors and updates device state.
 *
 * Handles proximity detection, water valve timing, status updates, and maintains
 * system responsiveness for touchless operation.
 */
void loop()
{
    // Update device state and process events
    faucetDevice.update();

    // Manual testing function (remove in production)
    testProximityDetection();

    // Small delay to prevent excessive CPU usage
    delay(50);
}

/**
 * @brief Manual test function to simulate proximity detection
 * Call this function to test the system without physical sensor interaction
 */
void testProximityDetection()
{
    static unsigned long lastTest = 0;
    static bool testTriggered = false;

    // Trigger test after 10 seconds, then every 20 seconds
    if (!testTriggered && millis() > 10000)
    {
        Serial.println("=== MANUAL TEST: Simulating proximity detection ===");
        faucetDevice.on(UltrasoundSensor::PROXIMITY_DETECTED_EVENT);
        testTriggered = true;
        lastTest = millis();
    }
    else if (testTriggered && millis() - lastTest > 20000)
    {
        Serial.println("=== MANUAL TEST: Simulating proximity detection ===");
        faucetDevice.on(UltrasoundSensor::PROXIMITY_DETECTED_EVENT);
        lastTest = millis();
    }
}
