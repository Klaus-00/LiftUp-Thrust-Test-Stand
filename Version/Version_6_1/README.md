# Version 6.1: Work in Progress With INA219 for Current and Voltage Measurement

## Description
This version integrates the INA219 module for precise current and voltage measurement. It is a work in progress and not fully tested.

## Features
- PWM control with 5% increments.
- Current and voltage measurement using INA219.

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
- **INA219 SDA**: A4
- **INA219 SCL**: A5
- **Ground**: Connected to Arduino GND and ESC GND

## Hardware Required
- Arduino Uno
- ESC (Electronic Speed Controller)
- Brushless Motor
- Three Load Cells (thrust, left, right)
- HX711 Load Cell Amplifier
- Push Button
- LEDs (Armed/Safe indicators)
- INA219 Module
- Power Supply for ESC and Motor

## What It Prints
- PWM percentage.
- Current in A.
- Voltage in V.
- Power in W.