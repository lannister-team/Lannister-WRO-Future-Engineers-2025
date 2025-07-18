# Schemas

## What is This Section For?

This section explains the **hardware wiring** and introduces the main **components** in the WRO 2025 Future Engineers self-driving car project. The car is designed to detect surroundings, make decisions based on visual and distance data, and control its motion accordingly using various electronic modules.

## Table of Contents
- [Main Components](#1-main-components) 
- [Components in Detail](#2-components-in-detail)

## 1. Main Components

| Component              | Function                                                                 |
|------------------------|--------------------------------------------------------------------------|
| Raspberry Pi 5         | Vision processing and command generation                                 |
| Raspberry Pi Camera    | Captures real-time video for color/shape detection                       |
| Arduino Uno            | Handles sensor readings and actuator control                             |
| L298N H-Bridge         | Controls power direction and speed of the DC motor                       |
| DC Motor with Encoder  | Drives rear wheels and provides feedback on distance/speed, 300 RPM      |
| 3x Ultrasonic Sensors  | Detects nearby obstacles (front, left, right)                            |
| MPU6050 IMU            | Tracks orientation and Z-axis stability (via gyroscope/accelerometer)    |
| Servo Motor            | Acts as steering by controlling the angle of the front wheels            |
| 12V Battery            | External power source for motor driver and motor                         |
| Breadboard             | Distributes power and ground to connected modules                        |

## 2. Components in Detail

### Raspberry Pi 5 (8 GB RAM) & Raspberry Pi Camera Module V3

- **Purpose:** Detect obstacle color and shape.
- **Why:** Arduino is not efficient for color detection or running AI code.
- **Communication:** Sends commands (RED, GREEN, NONE) to the Arduino Uno via Serial (UART). 
- **Powered by:** Powerbank

### Arduino Uno

- **Purpose:** Main controller for actuators (DC motor, servo) and sensors (ultrasonics, IMU, encoder).
- **Why:** Sufficient for controlling the sensors in this car; it's cheap and easy to use.
- **Communication:** Receives commands from Raspberry Pi via Serial (UART); controls devices via GPIO.
- **Powered by:** Raspberry Pi 5

### Ultrasonic Sensors (3x)

- **Purpose:** Detect obstacles to the front, left, and right for collision avoidance.
- **Placement:** Front, Left, Right
- **Communication:** Trig & Echo
- **Powered by:** Arduino 5V

### DC Motor with Encoder and L298N H-Bridge

#### DC Motor
- **Purpose:** Drives the car forward or backward.
- **Placement:** Rear wheels
- **Algorithm:** One DC motor is connected to a differential to move both wheels.  
  ➤ Read more: [Differential](../models/differential.md)
- **Communication:** Via L298N H-Bridge
- **Powered by:** L298N H-Bridge

#### Encoder
- **Purpose:** Measures distance and speed to provide feedback for control.
- **Placement:** Inside the DC motor
- **Communication:** Directly to Arduino pins
- **Powered by:** Arduino 5V

#### L298N H-Bridge
- **Purpose:**
  - Controls motor direction and speed
  - Amplifies the current required for the motor
- **Placement:** Centered near the motor
- **Communication:** Controlled by Arduino pins
- **Powered by:** 3x (3.7 Li-Ion) battery

### MPU6050 (IMU)

- **Purpose:** Reports angular motion, especially on the Z-axis (left/right turns).
- **Communication:** I2C protocol
- **Powered by:** Arduino 5V

### Servo Motor

- **Purpose:** Acts as the steering mechanism for the front wheels.
- **Why:** Provides realistic steering behavior (Ackermann steering geometry).
- **Algorithm:** The servo is connected to a linkage that controls the Ackermann steering system.  
  ➤ Read more: [Ackermann Steering System](../models/ackermann_ss.md)
- **Communication:** Controlled by Arduino pins
- **Powered by:** Arduino 5V

---
