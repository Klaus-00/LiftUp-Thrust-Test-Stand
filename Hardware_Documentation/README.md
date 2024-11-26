# **Hardware Documentation**

## **Thrust Test Stand Project**

This document outlines the hardware components necessary to build the Thrust Test Stand and provides information on how to connect them properly. 

The Thrust Test Stand is designed to test motors and propellers for aeronautical projects, measuring their performance in terms of thrust, torque, and PWM control.

---

## **Required Components**

### 1. **Microcontroller**  
- **Model**: Arduino Uno  
- **Purpose**: Main controller for managing motor control and sensor readings.

### 2. **Motor ESC (Electronic Speed Controller)**  
- **Model**: Compatible ESC for brushless motors (e.g., Hobbywing Platinum 60A).  
- **Connections**:  
  - Signal pin connected to PWM pin on Arduino.  
  - Ground pin connected to Arduino GND.  
  - Motor terminals connected to the motor.  

### 3. **Load Cells (3)**  
- **Left Cell**: Measures torque.  
- **Right Cell**: Measures torque (inverted factor for torque calculations).  
- **Thrust Cell**: Measures thrust force.  
- **Model**: Load cells with a maximum range suitable for expected forces (e.g., 10kg).  

### 4. **HX711 Load Cell Amplifiers (3)**  
- **Purpose**: Amplifies and digitizes the load cell signals.  
- **Connections**: Each load cell requires an HX711 module.  

### 5. **Servo Motor or Brushless Motor**  
- **Model**: Any motor with ESC compatibility.  
- **Purpose**: Tested for performance.  

### 6. **LED Indicators (2)**  
- **Green LED**: Indicates the system is armed.  
- **Red LED**: Indicates the system is safe.  

### 7. **Push Button**  
- **Purpose**: Arms or disarms the system with single or double clicks.  

### 8. **Power Supply**  
- **Battery**: Suitable for motor and ESC requirements (e.g., LiPo 3S, 11.1V).  

---

## **Pinout**

### **Arduino Uno Pin Connections**

- **ESC Signal**: Pin 11 (PWM control for ESC).  
- **Load Cell (Left)**: Pin 3 (DT), Pin 2 (SCK) (via HX711).  
- **Load Cell (Right)**: Pin 4 (DT), Pin 5 (SCK) (via HX711).  
- **Load Cell (Thrust)**: Pin 6 (DT), Pin 7 (SCK) (via HX711).  
- **Red LED**: Pin 10 (Safe status indicator).  
- **Green LED**: Pin 8 (Armed status indicator).  
- **Push Button**: Pin 12 (Arm/Disarm system).  

---

## **Setup Instructions**

### 1. **Connect Load Cells to HX711 Modules**:  
- **Wiring**:  
  - **E+ and E-**: Connect to the load cell excitation pins.  
  - **A+ and A-**: Connect to the signal pins on the load cell.  
- **Connection to Arduino**:  
  - Connect the DT and SCK pins of each HX711 module to the specified Arduino pins.

### 2. **Connect ESC to Arduino**:  
- Signal wire from the ESC to Arduino pin 11.  
- Connect ESC ground to Arduino GND.  
- Ensure the motor terminals are connected to the ESC.  

### 3. **Power Supply**:  
- Use a LiPo battery to power the ESC and motor.  
- Connect the battery directly to the ESC's power input.  

### 4. **LED Indicators**:  
- Green LED (armed) to pin 8 and red LED (safe) to pin 10.  
- Use appropriate resistors to limit current to the LEDs.

### 5. **Push Button**:  
- Connect the push button to pin 12 and GND.  

---

## **Safety Notes**
- Double-check all connections before powering the system.  
- Test the motor without the propeller first.
- Ensure the propeller is securely mounted to avoid accidents.  
- Conduct tests in an open and safe environment to prevent damage or injury.  

---


For further assistance or details, contact the LiftUp project team at the University of Padova.
