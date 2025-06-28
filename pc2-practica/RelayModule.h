#ifndef RELAY_MODULE_H
#define RELAY_MODULE_H

/**
 * @file RelayModule.h
 * @brief Declares the RelayModule class.
 *
 * A concrete actuator class in the Modest IoT Nano-framework for controlling relay modules.
 * Used in the Moen Cia Steel Faucet to control the water valve with timed operations
 * for precise flow control.
 *
 * @author Your Name - Moen Inc. Development Team
 * @date June 27, 2025
 * @version 1.0
 */

/*
 * This file is part of the Moen Cia Steel Faucet project.
 * Developed using the Modest IoT Nano-framework (C++ Edition).
 */

#include "Actuator.h"

class RelayModule : public Actuator
{
private:
    bool state;                   ///< Current state of the relay (true = OPEN/ON, false = CLOSED/OFF)
    unsigned long timerStartTime; ///< Start time for timed operations
    unsigned long timerDuration;  ///< Duration for timed operations in milliseconds
    bool timerActive;             ///< Flag indicating if timer is active

public:
    static const int OPEN_VALVE_COMMAND_ID = 10;       ///< Unique ID for open valve command
    static const int CLOSE_VALVE_COMMAND_ID = 11;      ///< Unique ID for close valve command
    static const int OPEN_VALVE_TIMED_COMMAND_ID = 12; ///< Unique ID for timed open valve command
    static const Command OPEN_VALVE_COMMAND;           ///< Predefined command to open the valve
    static const Command CLOSE_VALVE_COMMAND;          ///< Predefined command to close the valve
    static const Command OPEN_VALVE_TIMED_COMMAND;     ///< Predefined command to open valve for duration

    /**
     * @brief Constructs a RelayModule actuator.
     * @param pin The GPIO pin for the relay control (configured as OUTPUT).
     * @param initialState Initial state of the relay (default: false/CLOSED).
     * @param commandHandler Optional handler to receive commands (default: nullptr).
     */
    RelayModule(int pin, bool initialState = false, CommandHandler *commandHandler = nullptr);

    /**
     * @brief Handles commands to control the relay state.
     * @param command The command to execute (e.g., OPEN_VALVE_COMMAND).
     */
    void handle(Command command) override;

    /**
     * @brief Opens the water valve for a specified duration.
     * @param durationMs Duration to keep valve open in milliseconds.
     */
    void openValveTimed(unsigned long durationMs);

    /**
     * @brief Opens the water valve indefinitely.
     */
    void openValve();

    /**
     * @brief Closes the water valve.
     */
    void closeValve();

    /**
     * @brief Updates the timed operation status. Should be called regularly in loop().
     */
    void updateTimer();

    /**
     * @brief Gets the current state of the relay.
     * @return True if valve is OPEN, false if CLOSED.
     */
    bool getState() const;

    /**
     * @brief Gets the current state as a string for display.
     * @return "open" if valve is open, "closed" if closed.
     */
    const char *getStateString() const;

    /**
     * @brief Checks if a timed operation is currently active.
     * @return True if timer is active, false otherwise.
     */
    bool isTimerActive() const;
};

#endif // RELAY_MODULE_H
