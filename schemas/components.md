# Schemas

## 1. What is This Section For?

This section explains the **hardware wiring** and showing main **components** in the WRO 2025 Future Engineers self-driving car project. The car is designed to detect surroundings, make decisions based on visual and distance data, and control its motion accordingly using various electronic modules.

## 2. Main Components

| Component              | Function                                                                 |
|------------------------|--------------------------------------------------------------------------|
| Raspberry Pi 5         | Vision processing and command generation                                 |
| Raspberry Pi Camera    | Captures real-time video for color/shape detection                       |
| Arduino Uno            | Handles sensor readings and actuator control                             |
| L298N H-Bridge         | Controls power direction and speed of the DC motor                       |
| DC Motor with Encoder  | Drives rear wheels and provides feedback on distance/speed               |
| 3x Ultrasonic Sensors  | Detects nearby obstacles (front, left, right)                            |
| MPU6050 IMU            | Tracks orientation and Z-axis stability (via gyroscope/accelerometer)    |
| Servo Motor            | Acts as steering by controlling the angle of the front wheels            |
| 9V Battery             | External power source for motor driver and motor                         |
| Breadboard             | Distributes power and ground to connected modules                        |

## 3. Detailed Wiring and Functionality

### Raspberry Pi 5 (8 GB RAM) & Raspberry Pi Camera Module V3

- Purpose: Detect obstacle color and shape.
- Communication: Sends commands (`RED`, `GREEN`, `NONE`) to the Arduino Uno via Serial (UART).
- Why: Arduino may not be that efficient to detect colors.

### Arduino Uno

- Purpose: Central controller for actuators (DC motor, servo) and sensors (ultrasonics, IMU, encoder).
- Communication: Raspberry Pi via Serial (UART) and actuators/sensors through different protocol.

### Three Ultrasonic Sensors 

- Purpose: Detect obstacles to the sides and front for collision avoidance.
- Communication: Trig & Echo.
- Placement: Front, Left, Right.

### DC Motor with Encoder

- Purpose:
  - Drive the car forward or backward.

- Communication: L298N H-Bridge.
- Placement On: Rear wheels.

- Encoder Purpose: Allows us to measure how far the car has moved and regulate speed.
- L298N H-Bridge Purpose:
  - Controls direction and speed using PWM signals.
  - Handles higher current needed for the motor.
- Powered By: 9V battery (external power) to separate motor current from control electronics, preventing brownouts.

### MPU6050 (IMU)

- Purpose: Constantly reports angular movement, especially on the Z-axis (left/right turns).
- Communication: I2C (SCL/SDA - A4/A5) .

### Servo Motor

- Purpose: Acts as steering mechanism for the front wheels.
- Communication: Arduino PWM signal.
