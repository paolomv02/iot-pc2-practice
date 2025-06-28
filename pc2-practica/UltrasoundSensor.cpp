/**
 * @file UltrasoundSensor.cpp
 * @brief Implements the UltrasoundSensor class.
 *
 * Manages ultrasonic distance measurement in the Modest IoT Nano-framework for the
 * Moen Cia Steel Faucet MotionSense Wave™ technology. Provides proximity detection
 * capabilities for touchless water valve control.
 *
 * @author Your Name - Moen Inc. Development Team
 * @date June 27, 2025
 * @version 1.0
 */

/*
 * This file is part of the Moen Cia Steel Faucet project.
 * Developed using the Modest IoT Nano-framework (C++ Edition).
 */

#include "UltrasoundSensor.h"
#include <Arduino.h>

const Event UltrasoundSensor::PROXIMITY_DETECTED_EVENT = Event(PROXIMITY_DETECTED_EVENT_ID);
const Event UltrasoundSensor::PROXIMITY_LOST_EVENT = Event(PROXIMITY_LOST_EVENT_ID);

UltrasoundSensor::UltrasoundSensor(int trigPin, int echoPin, int thresholdCm, EventHandler *eventHandler)
    : Sensor(trigPin, eventHandler), trigPin(trigPin), echoPin(echoPin),
      lastDistance(-1), threshold(thresholdCm)
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
}

float UltrasoundSensor::measureDistance()
{
    // Clear the trigger pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Send a 10µs pulse to trigger pin
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echo pin and calculate distance
    long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout

    if (duration == 0)
    {
        return -1; // No echo received
    }

    // Calculate distance in cm (speed of sound: 343 m/s)
    float distance = (duration * 0.0343) / 2;

    // Validate measurement range (2cm to 400cm typical for HC-SR04)
    if (distance < 2 || distance > 400)
    {
        return -1;
    }

    lastDistance = distance;
    return distance;
}

void UltrasoundSensor::checkProximity()
{
    static bool wasInRange = false;

    float currentDistance = measureDistance();

    if (currentDistance > 0)
    { // Valid measurement
        bool isInRange = (currentDistance <= threshold);

        if (isInRange && !wasInRange)
        {
            // Object entered proximity range
            on(PROXIMITY_DETECTED_EVENT);
            wasInRange = true;
        }
        else if (!isInRange && wasInRange)
        {
            // Object left proximity range
            on(PROXIMITY_LOST_EVENT);
            wasInRange = false;
        }
    }
}

float UltrasoundSensor::getLastDistance() const
{
    return lastDistance;
}

void UltrasoundSensor::setThreshold(int thresholdCm)
{
    threshold = thresholdCm;
}

int UltrasoundSensor::getThreshold() const
{
    return threshold;
}
