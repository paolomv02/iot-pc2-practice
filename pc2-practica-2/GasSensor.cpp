#include "GasSensor.h"
#include <Arduino.h>

const float GasSensor::RATIO_MQ2_CLEAN_AIR = 9.83;

GasSensor::GasSensor(int analogPin, int digitalPin)
    : analogPin(analogPin), digitalPin(digitalPin)
{
    mq2Sensor = new MQUnifiedsensor("ESP-32", 3.3, 12, analogPin, "MQ-2");
}

GasSensor::~GasSensor()
{
    delete mq2Sensor;
}

void GasSensor::initialize()
{
    // Set Parameters to detect PPM concentration for LPG
    mq2Sensor->setRegressionMethod(1);
    mq2Sensor->setA(574.25);
    mq2Sensor->setB(-2.222);

    // MQ2 Init
    mq2Sensor->init();

    // Digital pin setup
    pinMode(digitalPin, INPUT);
}

void GasSensor::calibrate()
{
    Serial.print("Calibrating GasSensor, please wait.");
    float calcR0 = 0;

    for (int i = 1; i <= 10; i++)
    {
        mq2Sensor->update();
        calcR0 += mq2Sensor->calibrate(RATIO_MQ2_CLEAN_AIR);
        Serial.print(".");
    }

    mq2Sensor->setR0(calcR0 / 10);
    Serial.println();
    Serial.print("R0 calibrated: ");
    Serial.println(calcR0 / 10);

    // Exception Handling
    if (isinf(calcR0))
    {
        Serial.println("Warning: R0 value is infinite. Check wiring.");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        Serial.println("Warning: R0 value is zero. Check wiring.");
        while (1)
            ;
    }
}

void GasSensor::update()
{
    mq2Sensor->update();
    mq2Sensor->readSensor();
}

float GasSensor::readPPM()
{
    return mq2Sensor->readSensorR();
}

int GasSensor::readPercentage()
{
    int gasValue = analogRead(analogPin);
    return map(gasValue, 0, 4095, 0, 100);
}

GasLevel GasSensor::getGasLevel()
{
    float ppm = readPPM();

    if (ppm < SAFE_THRESHOLD)
    {
        return GasLevel::SAFE;
    }
    else if (ppm < CRITICAL_THRESHOLD)
    {
        return GasLevel::MODERATE;
    }
    else
    {
        return GasLevel::CRITICAL;
    }
}

bool GasSensor::isDigitalHigh()
{
    return digitalRead(digitalPin) == HIGH;
}

String GasSensor::getStatusText()
{
    GasLevel level = getGasLevel();

    switch (level)
    {
    case GasLevel::SAFE:
        return "SAFE";
    case GasLevel::MODERATE:
        return "MODERATE";
    case GasLevel::CRITICAL:
        return "CRITICAL";
    default:
        return "UNKNOWN";
    }
}
