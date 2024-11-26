# Version 6: Non-Functional Version With Analog Current and Voltage Measurement

## Description
This version attempts to integrate analog current and voltage sensors for power measurement. Due to issues with sensor accuracy, this version is non-functional.

## Features
- PWM control with 5% increments.
- Attempted current and voltage measurement.

## Pinout
- **ESC Signal**: Pin 11
- **Load Cell Left (DT)**: Pin 3
- **Load Cell Left (SCK)**: Pin 2
- **Load Cell Right (DT)**: Pin 4
- **Load Cell Right (SCK)**: Pin 5
- **Load Cell Thrust (DT)**: Pin 6
- **Load Cell Thrust (SCK)**: Pin 7
- **Button**: Pin 12
- **LED Armed**: Pin 8
- **LED Safe**: Pin 10
- **Analog Current**: A3
- **Analog Voltage**: A1
- **Ground**: Connected to Arduino GND and ESC GND

## Hardware Required
- Arduino Uno
- ESC (Electronic Speed Controller)
- Brushless Motor
- Three Load Cells (thrust, left, right)
- HX711 Load Cell Amplifier
- Push Button
- LEDs (Armed/Safe indicators)
- Analog Current and Voltage Sensors
- Power Supply for ESC and Motor

## What It Prints
- PWM percentage.
- Attempted current and voltage measurement.