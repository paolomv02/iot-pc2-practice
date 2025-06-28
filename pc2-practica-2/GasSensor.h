#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <MQUnifiedsensor.h>

enum class GasLevel
{
    SAFE,     // < 200 PPM
    MODERATE, // 200-500 PPM
    CRITICAL  // > 500 PPM
};

class GasSensor
{
private:
    MQUnifiedsensor *mq2Sensor;
    int analogPin;
    int digitalPin;
    static const float RATIO_MQ2_CLEAN_AIR;
    static const int SAFE_THRESHOLD = 200;
    static const int CRITICAL_THRESHOLD = 500;

public:
    GasSensor(int analogPin, int digitalPin);
    ~GasSensor();

    void initialize();
    void calibrate();
    void update();
    float readPPM();
    int readPercentage();
    GasLevel getGasLevel();
    bool isDigitalHigh();
    String getStatusText();
};

#endif
