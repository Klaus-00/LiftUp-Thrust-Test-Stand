# Version 5: Definitive Version Without Current and Voltage Measurement

## Description
This version integrates all previous features, including thrust and torque measurement, button control, and PWM testing. Current and voltage measurement are excluded.

## Features
- Button control for arming/disarming and double-click to start the test.
- Thrust and torque measurement using three load cells.
- Adjustable test duration.
- PWM control with 5% increments.

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
- **Ground**: Connected to Arduino GND and ESC GND

## Hardware Required
- Arduino Uno
- ESC (Electronic Speed Controller)
- Brushless Motor
- Three Load Cells (thrust, left, right)
- HX711 Load Cell Amplifier
- Push Button
- LEDs (Armed/Safe indicators)
- Power Supply for ESC and Motor

## What It Prints
- PWM percentage.
- Thrust in kg and N.
- Left cell in kg and N.
- Right cell in kg and N.
- Torque in kg and N.