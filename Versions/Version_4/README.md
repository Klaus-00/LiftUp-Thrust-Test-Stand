# Version 4: Adding Button Control for Arm/Disarm and Double Click for Test

## Description
This version introduces a single button for arming/disarming the system. A double-click initiates the test.

## Features
- Button control for arming and disarming.
- Double-click to start the test.
- PWM, thrust, and torque measurements.

## Pinout
- **ESC Signal**: Pin 11
- **Load Cell Left (DT)**: Pin 3
- **Load Cell Left (SCK)**: Pin 2
- **Load Cell Right (DT)**: Pin 4
- **Load Cell Right (SCK)**: Pin 5
- **Button**: Pin 12
- **LED Armed**: Pin 8
- **LED Safe**: Pin 10
- **Ground**: Connected to Arduino GND and ESC GND

## Hardware Required
- Arduino Uno
- ESC (Electronic Speed Controller)
- Brushless Motor
- Two Load Cells (for torque)
- HX711 Load Cell Amplifier
- Push Button
- LEDs (Armed/Safe indicators)
- Power Supply for ESC and Motor

## What It Prints
- PWM percentage.
- Thrust in kg and N.
- Torque in kg and N.