/*
 * GLP SecureSense Pro - IoT Gas Detection System
 * Protech Innovations, Inc.
 *
 * This embedded application implements an object-oriented solution
 * for monitoring LPG gas concentrations with visual LED indicators
 * and enhanced display information using a 20x4 LCD.
 *
 * Features:
 * - Real-time LPG concentration monitoring in PPM
 * - Three-level safety indication (Safe, Moderate, Critical)
 * - LED status indicators (Green, Yellow, Red)
 * - Enhanced 20x4 LCD display with comprehensive information
 * - Serial logging for monitoring and debugging
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MQUnifiedsensor.h>
#include "GLPSecureSenseDevice.h"

// Global device instance
GLPSecureSenseDevice *glpDevice;

void setup()
{
  // Create and initialize the GLP SecureSense Pro device
  glpDevice = new GLPSecureSenseDevice();
  glpDevice->initialize();
}

void loop()
{
  // Run the main device operations
  glpDevice->run();

  // Small delay to prevent overwhelming the system
  delay(100);
}
