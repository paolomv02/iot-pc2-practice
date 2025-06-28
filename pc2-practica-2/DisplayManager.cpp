#include "DisplayManager.h"
#include <Arduino.h>

DisplayManager::DisplayManager(uint8_t address) : lastUpdate(0)
{
    lcd = new LiquidCrystal_I2C(address, COLS, ROWS);
}

DisplayManager::~DisplayManager()
{
    delete lcd;
}

void DisplayManager::initialize()
{
    lcd->init();
    lcd->begin(COLS, ROWS);
    lcd->backlight();
    clear();
}

void DisplayManager::showStartupMessage()
{
    clear();
    lcd->setCursor(2, 1);
    lcd->print("GLP SecureSense Pro");
    lcd->setCursor(4, 2);
    lcd->print("Protech Innovations");
    delay(2000);

    clear();
    lcd->setCursor(6, 1);
    lcd->print("Initializing");
    lcd->setCursor(7, 2);
    lcd->print("System...");
    delay(1000);
}

void DisplayManager::showCalibrationStatus(float r0Value)
{
    clear();
    lcd->setCursor(4, 1);
    lcd->print("Calibrating...");
    lcd->setCursor(2, 2);
    lcd->print("R0 = ");
    lcd->print(r0Value, 2);
    delay(1000);
}

void DisplayManager::updateDisplay(float ppm, int percentage, GasLevel level, String status)
{
    unsigned long currentTime = millis();
    if (currentTime - lastUpdate < UPDATE_INTERVAL)
    {
        return;
    }

    clear();
    displayHeader();
    displayGasData(ppm, percentage);
    displayStatus(level, status);
    displayTimestamp();

    lastUpdate = currentTime;
}

void DisplayManager::showErrorMessage(String error)
{
    clear();
    lcd->setCursor(0, 1);
    lcd->print("ERROR:");
    lcd->setCursor(0, 2);
    lcd->print(error);
}

void DisplayManager::clear()
{
    lcd->clear();
}

void DisplayManager::displayHeader()
{
    lcd->setCursor(0, 0);
    lcd->print("=== GLP MONITOR ===");
}

void DisplayManager::displayGasData(float ppm, int percentage)
{
    lcd->setCursor(0, 1);
    lcd->print("LPG: ");
    lcd->print(formatPPM(ppm));
    lcd->print(" PPM");

    lcd->setCursor(0, 2);
    lcd->print("Level: ");
    lcd->print(percentage);
    lcd->print("%");
}

void DisplayManager::displayStatus(GasLevel level, String status)
{
    lcd->setCursor(0, 3);
    lcd->print("Status: ");
    lcd->print(getLevelIndicator(level));
    lcd->print(" ");
    lcd->print(status);
}

void DisplayManager::displayTimestamp()
{
    unsigned long seconds = millis() / 1000;
    unsigned long minutes = seconds / 60;
    seconds = seconds % 60;

    lcd->setCursor(14, 1);
    if (minutes < 10)
        lcd->print("0");
    lcd->print(minutes);
    lcd->print(":");
    if (seconds < 10)
        lcd->print("0");
    lcd->print(seconds);
}

String DisplayManager::formatPPM(float ppm)
{
    if (ppm < 1000)
    {
        return String((int)ppm);
    }
    else
    {
        return String(ppm / 1000.0, 1) + "K";
    }
}

String DisplayManager::getLevelIndicator(GasLevel level)
{
    switch (level)
    {
    case GasLevel::SAFE:
        return "[G]"; // Green indicator
    case GasLevel::MODERATE:
        return "[Y]"; // Yellow indicator
    case GasLevel::CRITICAL:
        return "[R]"; // Red indicator
    default:
        return "[?]";
    }
}
