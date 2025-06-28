/**
 * @file CiaSteelFaucet.cpp
 * @brief Implements the CiaSteelFaucet device class.
 *
 * Main implementation for the Moen Cia Steel Faucet with MotionSense Wave™ technology.
 * Coordinates proximity sensing, LED indication, water valve control, and WiFi connectivity
 * for the Smart Water Network ecosystem.
 *
 * @author Your Name - Moen Inc. Development Team
 * @date June 27, 2025
 * @version 1.0
 */

/*
 * This file is part of the Moen Cia Steel Faucet project.
 * Developed using the Modest IoT Nano-framework (C++ Edition).
 */

#include "CiaSteelFaucet.h"
#include <Arduino.h>

CiaSteelFaucet::CiaSteelFaucet(const char *wifiSSID, const char *wifiPassword)
    : proximitydetector(ULTRASOUND_TRIG_PIN, ULTRASOUND_ECHO_PIN, PROXIMITY_THRESHOLD_CM, this),
      waterValve(RELAY_PIN, false, this),
      statusLed(LED_PIN, false, this),
      lastStatusUpdate(0),
      statusUpdateInterval(STATUS_UPDATE_INTERVAL_MS),
      ssid(wifiSSID),
      password(wifiPassword),
      wifiConnected(false)
{
}

void CiaSteelFaucet::initialize()
{
    Serial.begin(115200);
    delay(1000); // Allow serial to initialize

    printWelcomeMessage();

    // Initialize WiFi if credentials provided
    if (ssid != nullptr && password != nullptr)
    {
        initializeWiFi();
    }

    // Device is now active - turn on status LED
    statusLed.setState(true);

    Serial.println("Moen Cia Steel Faucet initialized successfully.");
    Serial.println("MotionSense Wave™ technology is now active.");
    Serial.println("Monitoring for proximity within 10cm threshold...");
    Serial.println();

    lastStatusUpdate = millis();
}

void CiaSteelFaucet::update()
{
    // Check for proximity events
    proximitydetector.checkProximity();

    // Update water valve timer
    waterValve.updateTimer();

    // Print status periodically
    if (millis() - lastStatusUpdate >= statusUpdateInterval)
    {
        printStatus();
        lastStatusUpdate = millis();
    }
}

void CiaSteelFaucet::on(Event event)
{
    if (event == UltrasoundSensor::PROXIMITY_DETECTED_EVENT)
    {
        Serial.println(">>> Proximity detected! Hand approaching faucet.");

        // Turn on LED to indicate detection
        statusLed.setState(true);

        // Open water valve for 5 seconds
        waterValve.openValveTimed(VALVE_OPEN_DURATION_MS);

        Serial.println(">>> Water valve opened for 5 seconds.");
    }
    else if (event == UltrasoundSensor::PROXIMITY_LOST_EVENT)
    {
        Serial.println(">>> Proximity lost. Hand moved away from faucet.");

        // Keep LED on (device remains active)
        // Water valve will close automatically after timer expires
    }
}

void CiaSteelFaucet::handle(Command command)
{
    // Handle any external commands if needed
    // For now, relay commands to water valve
    if (command == RelayModule::OPEN_VALVE_COMMAND ||
        command == RelayModule::CLOSE_VALVE_COMMAND ||
        command == RelayModule::OPEN_VALVE_TIMED_COMMAND)
    {
        waterValve.handle(command);
    }

    // Handle LED commands
    if (command == Led::TURN_ON_COMMAND ||
        command == Led::TURN_OFF_COMMAND ||
        command == Led::TOGGLE_LED_COMMAND)
    {
        statusLed.handle(command);
    }
}

void CiaSteelFaucet::printWelcomeMessage()
{
    Serial.println("=====================================");
    Serial.println("        MOEN, INC.");
    Serial.println("   Cia Steel Faucet with");
    Serial.println("   MotionSense Wave™ Technology");
    Serial.println("=====================================");
    Serial.println();
    Serial.println("Innovating water solutions since 1937");
    Serial.println("Smart Water Network Technology");
    Serial.println("Maximum Flow: 1.2 GPM (4.5L/min) @ 60 PSI");
    Serial.println();
    Serial.println("Developer: [Your Name]");
    Serial.println("Team: Moen Inc. Development Team");
    Serial.println("Version: 1.0");
    Serial.println("Date: June 27, 2025");
    Serial.println();
    Serial.println("Features:");
    Serial.println("- Touchless proximity detection (10cm threshold)");
    Serial.println("- Automatic 5-second water flow");
    Serial.println("- Smart Water Network connectivity");
    Serial.println("- Blue LED status indication");
    Serial.println("=====================================");
    Serial.println();
}

void CiaSteelFaucet::printStatus()
{
    float distance = proximitydetector.getLastDistance();
    const char *valveState = waterValve.getStateString();

    Serial.println("--- Moen Cia Steel Faucet Status ---");

    if (distance >= 0)
    {
        Serial.printf("Proximity: %.1f cm", distance);
        if (distance <= PROXIMITY_THRESHOLD_CM)
        {
            Serial.print(" [DETECTED]");
        }
        Serial.println();
    }
    else
    {
        Serial.println("Proximity: No reading");
    }

    Serial.printf("Water Valve: %s", valveState);
    if (waterValve.isTimerActive())
    {
        Serial.print(" [TIMED]");
    }
    Serial.println();

    Serial.printf("Status LED: %s\n", statusLed.getState() ? "ON" : "OFF");

    if (wifiConnected)
    {
        Serial.printf("WiFi: Connected to %s (IP: %s)\n", ssid, WiFi.localIP().toString().c_str());
    }
    else
    {
        Serial.println("WiFi: Not connected");
    }

    Serial.println("------------------------------------");
    Serial.println();
}

void CiaSteelFaucet::initializeWiFi()
{
    Serial.printf("Connecting to WiFi network: %s", ssid);

    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        wifiConnected = true;
        Serial.println();
        Serial.println("WiFi connected successfully!");
        Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());
        Serial.println("Ready for Smart Water Network integration.");
    }
    else
    {
        wifiConnected = false;
        Serial.println();
        Serial.println("WiFi connection failed. Operating in offline mode.");
    }
    Serial.println();
}

UltrasoundSensor &CiaSteelFaucet::getProximitydetector()
{
    return proximitydetector;
}

RelayModule &CiaSteelFaucet::getWaterValve()
{
    return waterValve;
}

Led &CiaSteelFaucet::getStatusLed()
{
    return statusLed;
}

bool CiaSteelFaucet::isWiFiConnected() const
{
    return wifiConnected;
}
