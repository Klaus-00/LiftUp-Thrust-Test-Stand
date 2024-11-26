# liftup

# **Thrust Test Stand for Project LiftUp**

## **General Overview**

The **Thrust Test Stand** is a precision measurement device designed for testing and evaluating motors and propellers used in aerial vehicles. Developed as part of the **LiftUp Project** at the **University of Padova**, this stand allows researchers and students to gather critical performance data such as thrust and torque, enabling optimization of propulsion systems. 

This tool is essential for experimental aeronautical engineering, especially for student-led projects aiming to design and test innovative aerial vehicles. It provides a hands-on platform to learn and apply principles of aerodynamics and propulsion engineering.

---

## **Key Features and Capabilities**

1. **Motor Speed Control:**
   - The stand uses PWM (Pulse Width Modulation) signals to precisely control motor speed via an ESC (Electronic Speed Controller).

2. **Force and Torque Measurement:**
   - A thrust load cell measures the force generated along the motor's axis (in kg and N).
   - Two side-mounted load cells calculate torque by measuring differential forces (also in kg and N).

3. **System Status Indicators:**
   - **LED Indicators:** 
     - A green LED signals the system is armed and ready for testing.
     - A red LED signals the system is disarmed and safe.
   - **User Control:**
     - A single button for system control, featuring single and double-click functionalities for arming, disarming, and starting tests.

4. **Data Output:**
   - Real-time data including:
     - PWM percentage.
     - Thrust in kg and N.
     - Individual load cell measurements in kg and N.
     - Calculated torque in kg and N.

5. **Calibration Routines:**
   - Easy-to-use calibration scripts for load cells, allowing precise tuning with known weights.

6. **Modularity and Scalability:**
   - Multiple versions of the code demonstrate incremental feature development, from basic motor control to multi-load cell torque calculation.

---

## **How It Works**

### **System Overview**

1. **Load Cells:**
   - Three load cells are connected to HX711 amplifiers for precision weight and force measurement.
     - **Thrust Load Cell:** Measures the force along the motor's axis.
     - **Left and Right Load Cells:** Measure forces for torque calculation.

2. **ESC and Motor:**
   - The motor's speed is controlled by an ESC, which receives PWM signals from the Arduino.

3. **Arduino Microcontroller:**
   - Central control unit that handles:
     - PWM generation for motor control.
     - Data acquisition from load cells.
     - User input and LED feedback.
     - Serial data output for analysis.

4. **User Interaction:**
   - A single button controls the system:
     - **Single Click:** Arm or disarm the system.
     - **Double Click:** Start the calibration and testing sequence.

### **Calibration**

Calibration scripts for the load cells are included in the repository. These scripts ensure accurate force and torque readings by applying known weights during the calibration process. For best results:
- Use weights that are close to the maximum expected force.
- Update the calibration factor in the script based on the results.

### **Testing Procedure**

1. **Setup:**
   - Connect the motor, ESC, and load cells to the Arduino.
   - Ensure the system is powered and the load cells are properly mounted.

2. **Arming the System:**
   - Press the button once. The green LED will light up, indicating the system is armed.

3. **Starting the Test:**
   - Double-click the button. The red LED will turn off, and the test will begin.

4. **Test Execution:**
   - The motor speed will ramp up in 5% increments from the minimum to the maximum PWM percentage.
   - At each step, thrust, torque, and load cell data will be collected and displayed on the serial monitor.

5. **Disarming the System:**
   - Press the button once to disarm the system and ensure safety.

---

## **Hardware Requirements**

1. **Microcontroller:**
   - Arduino Uno (or compatible board).

2. **Sensors:**
   - Three HX711 amplifiers for load cells.
   - Three load cells for thrust and torque measurement.

3. **Motor and ESC:**
   - Motor and ESC compatible with PWM signals.

4. **Miscellaneous:**
   - Push button.
   - Two LEDs (green and red).
   - Power source for the motor and ESC.

---

## **Software Setup**

1. **Code Structure:**
   - The repository contains:
     - **Main Code:** Runs the test and outputs data.
     - **Calibration Scripts:** For tuning the load cells.
     - **Versioned Code:** Historical development stages for reference.

2. **Required Libraries:**
   - **Servo.h:** For ESC control.
   - **HX711.h:** For load cell amplification.

3. **Compilation:**
   - Open the `.ino` file in the Arduino IDE.
   - Ensure the correct board and port are selected.
   - Upload the code to the Arduino.

---

## **Output Data**

1. **Real-Time Serial Output:**
   - PWM percentage.
   - Thrust (kg and N).
   - Load cell measurements for left and right (kg and N).
   - Calculated torque (kg and N).

2. **Sample Output:**
PWM: 30.0% - Left: 1.20 kg, 11.78 N - Right: 1.25 kg, 12.27 N
Thrust: 2.45 kg, 24.05 N - Torque: 0.05 kg, 0.49 N
---

## **Future Enhancements**

1. **Current and Voltage Monitoring:**
- Integration of an INA219 module with a 100A shunt for precise power measurements.

2. **RPM Monitoring:**
- Adding a tachometer to measure motor speed.

3. **Automated Analysis:**
- Software tools to visualize and analyze data trends.

---

## **Conclusion**

The **Thrust Test Stand** is a powerful tool for understanding and optimizing motor and propeller performance. It offers students and researchers at the **University of Padova** a hands-on platform for real-world engineering applications, contributing to the success of the **LiftUp Project** and advancing knowledge in aeronautical engineering.
