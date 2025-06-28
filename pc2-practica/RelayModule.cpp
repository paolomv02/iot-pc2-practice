/**
 * @file RelayModule.cpp
 * @brief Implements the RelayModule class.
 *
 * Manages relay control for water valve operations in the Moen Cia Steel Faucet,
 * supporting both timed and manual valve control with precise timing for
 * MotionSense Wave™ functionality.
 *
 * @author Your Name - Moen Inc. Development Team
 * @date June 27, 2025
 * @version 1.0
 */

/*
 * This file is part of the Moen Cia Steel Faucet project.
 * Developed using the Modest IoT Nano-framework (C++ Edition).
 */

#include "RelayModule.h"
#include <Arduino.h>

const Command RelayModule::OPEN_VALVE_COMMAND = Command(OPEN_VALVE_COMMAND_ID);
const Command RelayModule::CLOSE_VALVE_COMMAND = Command(CLOSE_VALVE_COMMAND_ID);
const Command RelayModule::OPEN_VALVE_TIMED_COMMAND = Command(OPEN_VALVE_TIMED_COMMAND_ID);

RelayModule::RelayModule(int pin, bool initialState, CommandHandler *commandHandler)
    : Actuator(pin, commandHandler), state(initialState), timerStartTime(0),
      timerDuration(0), timerActive(false)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, state ? HIGH : LOW);
}

void RelayModule::handle(Command command)
{
    if (command == OPEN_VALVE_COMMAND)
    {
        openValve();
    }
    else if (command == CLOSE_VALVE_COMMAND)
    {
        closeValve();
    }
    else if (command == OPEN_VALVE_TIMED_COMMAND)
    {
        openValveTimed(5000); // Default 5 seconds as per requirements
    }

    Actuator::handle(command); // Propagate to handler if set
}

void RelayModule::openValveTimed(unsigned long durationMs)
{
    state = true;
    digitalWrite(pin, HIGH);
    timerStartTime = millis();
    timerDuration = durationMs;
    timerActive = true;
}

void RelayModule::openValve()
{
    state = true;
    digitalWrite(pin, HIGH);
    timerActive = false; // Cancel any active timer
}

void RelayModule::closeValve()
{
    state = false;
    digitalWrite(pin, LOW);
    timerActive = false; // Cancel any active timer
}

void RelayModule::updateTimer()
{
    if (timerActive && (millis() - timerStartTime >= timerDuration))
    {
        closeValve(); // Timer expired, close valve
    }
}

bool RelayModule::getState() const
{
    return state;
}

const char *RelayModule::getStateString() const
{
    return state ? "open" : "closed";
}

bool RelayModule::isTimerActive() const
{
    return timerActive;
}
