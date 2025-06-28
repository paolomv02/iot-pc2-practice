#ifndef LED_INDICATOR_H
#define LED_INDICATOR_H

#include "GasSensor.h"

class LedIndicator
{
private:
    int greenPin;
    int yellowPin;
    int redPin;

public:
    LedIndicator(int greenPin, int yellowPin, int redPin);
    void initialize();
    void updateStatus(GasLevel level);
    void turnOffAll();
    void testSequence();
};

#endif
