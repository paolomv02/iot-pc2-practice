#ifndef ULTRASOUND_SENSOR_H
#define ULTRASOUND_SENSOR_H

/**
 * @file UltrasoundSensor.h
 * @brief Declares the UltrasoundSensor class.
 *
 * A concrete sensor class in the Modest IoT Nano-framework for measuring distance using
 * ultrasonic technology. It extends the `Sensor` base class for proximity detection
 * in the Moen Cia Steel Faucet with MotionSense Wave™ technology.
 *
 * @author Your Name - Moen Inc. Development Team
 * @date June 27, 2025
 * @version 1.0
 */

/*
 * This file is part of the Moen Cia Steel Faucet project.
 * Developed using the Modest IoT Nano-framework (C++ Edition).
 */

#include "Sensor.h"

class UltrasoundSensor : public Sensor
{
private:
    int trigPin;        ///< Trigger pin for ultrasound sensor
    int echoPin;        ///< Echo pin for ultrasound sensor
    float lastDistance; ///< Last measured distance in cm
    int threshold;      ///< Proximity threshold in cm

public:
    static const int PROXIMITY_DETECTED_EVENT_ID = 10; ///< Unique ID for proximity detected event
    static const int PROXIMITY_LOST_EVENT_ID = 11;     ///< Unique ID for proximity lost event
    static const Event PROXIMITY_DETECTED_EVENT;       ///< Predefined event for proximity detection
    static const Event PROXIMITY_LOST_EVENT;           ///< Predefined event for proximity lost

    /**
     * @brief Constructs an UltrasoundSensor.
     * @param trigPin The GPIO pin for the trigger signal.
     * @param echoPin The GPIO pin for the echo signal.
     * @param thresholdCm Proximity threshold in centimeters (default: 10cm).
     * @param eventHandler Optional handler to receive sensor events (default: nullptr).
     */
    UltrasoundSensor(int trigPin, int echoPin, int thresholdCm = 10, EventHandler *eventHandler = nullptr);

    /**
     * @brief Measures the distance to an object in centimeters.
     * @return Distance in centimeters, or -1 if measurement failed.
     */
    float measureDistance();

    /**
     * @brief Checks for proximity events and triggers them if conditions are met.
     * Should be called periodically to monitor for proximity changes.
     */
    void checkProximity();

    /**
     * @brief Gets the last measured distance.
     * @return Last distance measurement in centimeters.
     */
    float getLastDistance() const;

    /**
     * @brief Sets the proximity threshold.
     * @param thresholdCm New threshold value in centimeters.
     */
    void setThreshold(int thresholdCm);

    /**
     * @brief Gets the current proximity threshold.
     * @return Threshold value in centimeters.
     */
    int getThreshold() const;
};

#endif // ULTRASOUND_SENSOR_H
