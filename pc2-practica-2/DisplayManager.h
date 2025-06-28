#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>
#include "GasSensor.h"

class DisplayManager
{
private:
    LiquidCrystal_I2C *lcd;
    static const int ROWS = 4;
    static const int COLS = 20;
    unsigned long lastUpdate;
    static const unsigned long UPDATE_INTERVAL = 500;

public:
    DisplayManager(uint8_t address);
    ~DisplayManager();

    void initialize();
    void showStartupMessage();
    void showCalibrationStatus(float r0Value);
    void updateDisplay(float ppm, int percentage, GasLevel level, String status);
    void showErrorMessage(String error);
    void clear();

private:
    void displayHeader();
    void displayGasData(float ppm, int percentage);
    void displayStatus(GasLevel level, String status);
    void displayTimestamp();
    String formatPPM(float ppm);
    String getLevelIndicator(GasLevel level);
};

#endif
