#include "LedIndicator.h"
#include <Arduino.h>

LedIndicator::LedIndicator(int greenPin, int yellowPin, int redPin)
    : greenPin(greenPin), yellowPin(yellowPin), redPin(redPin) {}

void LedIndicator::initialize()
{
    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    turnOffAll();
}

void LedIndicator::updateStatus(GasLevel level)
{
    turnOffAll();

    switch (level)
    {
    case GasLevel::SAFE:
        digitalWrite(greenPin, HIGH);
        break;
    case GasLevel::MODERATE:
        digitalWrite(yellowPin, HIGH);
        break;
    case GasLevel::CRITICAL:
        digitalWrite(redPin, HIGH);
        break;
    }
}

void LedIndicator::turnOffAll()
{
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
}

void LedIndicator::testSequence()
{
    turnOffAll();
    delay(200);

    digitalWrite(greenPin, HIGH);
    delay(500);
    digitalWrite(greenPin, LOW);

    digitalWrite(yellowPin, HIGH);
    delay(500);
    digitalWrite(yellowPin, LOW);

    digitalWrite(redPin, HIGH);
    delay(500);
    digitalWrite(redPin, LOW);
}
