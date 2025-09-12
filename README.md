<h1 align="center"><strong>Lannister Team</strong></h1>

<p align="center"><strong>WRO 2025 Local Final: Future Engineers</strong></p>

<p align="center">
  <img src="media/Logo_Team.png" alt="Lannister Team Logo" width="300"/>
</p>

<p align="center">
  This is the official repository of <strong>Team Lannister</strong> for the international final of the <strong>WRO2025</strong> season.
</p>


# Engineering Materials Repository

This repository contains all materials related to our engineering vehicle project for the competition. The content is organized into several folders as described below.

---

##  Folder Structure

### `t-photos`
- Contains **2 team photos**:
  - An **official team photo**.
  - A **funny photo** with all team members.

### `v-photos`
- Contains **6 photos of the vehicle**:
  - Captured from **every side**, as well as from the **top and bottom**.

### `video`
- Contains a `video.md` file with a **link to a demonstration video** showing the vehicle in action.

### `schemes`
- Contains **schematic diagrams** in **JPEG**, **PNG**, or **PDF** format.
- Illustrates all **electromechanical components** used in the vehicle:
  - Electronic components
  - Motors
  - Wiring and connections between them

### `src`
- Contains the **source code** for the control software.
- Includes all components programmed to participate in the competition.

### `models`

- Contains **illustrative diagrams and conceptual models** related to the mechanical design of the robot, including:
  - *Ackermann Steering System in Our WRO 2025 Car*
  - *Differential Gear System in Our WRO 2025 Car*
- These models are used for documentation and explanation purposes only, and do not include 3D-printable or CNC-ready files.
- This folder helps visualize how steering and torque distribution are mechanically implemented in the vehicle.


### `media`
- Contains **images and diagrams** used throughout the documentation, including:
  - Photos of hardware components (motors, sensors, controllers, etc.)
  - System wiring diagrams or mechanical schematics
  - Illustrations for the README and other documentation
- May also include other helpful files such as:
  - Datasets
  - Connection instructions to SBC/SBM
  - Hardware specifications and communication protocols

---

##  Car Components

This structure ensures clear organization and ease of navigation for anyone working on, reviewing, or evaluating the engineering project.

Introduction
Hello, Team Lannister here, let's go a deeper into how this seasons robot is made up !!

### Mobility Management Components

| ![MG996R Servo](media/Servo_Motor.jpg) | ![JGB37-520 Encoder Gearmotor](media/JGB37_DC_MOTOR.jpg) |
|:----------------------------------:|:-------------------------------------------------:|
| **MG996R Servo Motor** <br><br>• Weight: ~55g  <br>• Dimensions: 40.7 × 19.7 × 42.9 mm  <br>• Stall torque: 9.4 kgf·cm at 4.8V <br>• Stall torque: 11 kgf·cm at 6.0V <br>• Speed: 0.20s/60° at 4.8V (no load) <br>• Speed: 0.16s/60° at 6.0V (no load) <br>• Rotational range: 180° <br>• Pulse width: 500–2500 µs | **JGB37-520 Encoder Gearmotor (12V, 530 RPM, 18.8:1)** <br><br>• Rated voltage: 12V <br>• Speed: up to 530 RPM (no load) <br>• Gear ratio: 18.8:1 <br>• Shaft diameter: 6 mm <br>• Motor diameter: 37 mm <br>• Encoder resolution: 11 pulses per revolution <br>• No load current: ~120mA <br>• Stall current: ~2.8A <br>• Stall torque: ~3.2 kgf·cm |




###  Motor Integration and Drive System

To ensure proper implementation of the DC 12V encoder gear motor and the servo motor, both a motor driver and a mechanical differential were selected as essential components of the drive system.

The encoder gear motor is responsible for powering the mechanical differential, which then distributes motion evenly to the rear wheels. This configuration was chosen due to the torque multiplication offered by the differential — a key factor for achieving precise maneuverability within constrained environments, such as a competition playing field.

The integrated gear reduction system in the motor provides several advantages:

- Simplified mechanical design  
- Enhanced power and torque output  
- High durability due to the sealed and enclosed housing  

This combination of components enables smooth, responsive, and reliable mobility suitable for both fine control and sustained movement under varying load conditions.

####  Drive System Overview

<p align="center">
  <img src="media/differntil_animation.gif" alt="Mechanical Differential" width="45%">
</p>

---

###  Ackermann Steering System

To achieve realistic turning behavior and reduce tire slip during sharp turns, the robot implements an **Ackermann steering mechanism**. This system is commonly used in cars and robotics for accurate cornering.

####  How it works:

When a vehicle turns, the inner front wheel must rotate at a **sharper angle** than the outer wheel. Ackermann steering geometry ensures this by linking the steering arms to pivot at a calculated angle, allowing the two front wheels to point towards the center of a turning circle.

This offers the following benefits:

- Reduced tire wear during turns  
- Improved energy efficiency  
- More accurate and realistic path-following behavior  
- Ideal for tight indoor environments like robotic competitions

<p align="center">
  <img src="media/Ackermann_photo.svg" alt="Ackermann Steering Diagram" width="55%">
</p>

---


###  System Elements Overview

This section outlines the main hardware components integrated into the robot, including control units, sensors, power elements, and motor drivers.

---


####  Microcontrollers and Computing Units

### Arduino Uno

The Arduino Uno serves as the main microcontroller responsible for low-level control tasks such as motor actuation and sensor data acquisition. It interfaces directly with the motor driver, sensors, and power supply through individual wiring and connections without the use of a custom shield.

Connections are managed via standard Arduino input/output pins, with careful wiring to ensure stable power distribution and reliable communication with all peripheral components.

<p align="center">
  <img src="media/arduino_animation.gif" alt="Arduino Uno" width="45%">
</p>

### Raspberry Pi 5 (Model B)

The Raspberry Pi 5 serves as the high-level processing unit, handling tasks such as path planning, camera data processing, and advanced control logic. Model B features a quad-core ARM Cortex-A76 processor running at 2.4GHz, up to 8GB RAM, dual 4K display output, USB 3.0 support, Gigabit Ethernet, built-in Wi-Fi and Bluetooth 5.0.

<p align="center">
  <img src="media/RPI5_animation.gif" alt="Raspberry Pi 5" width="45%">
</p>

---

####  Vision System

- **Raspberry Pi Camera Module**  
  The robot is equipped with the official Raspberry Pi Camera Module, providing real-time video input for image-based navigation or line-following tasks. The camera is directly connected to the Pi via the CSI interface for low-latency image capture.

<p align="center">
  <img src="media/Raspberry_Pi_Camera.jpg" alt="Raspberry Pi Camera Module" width="40%">
</p>


---

####  Motors and Actuation

- **Motors Configuration**  
  The robot includes:
  - **1 DC Encoder Gearmotor** for rear-wheel drive (forward and backward motion).
  - **1 SG90 Servomotor** for steering the front wheels (left/right movement).

  These motors work together to allow omnidirectional navigation on a flat surface. Specifications include:
  - Torque: ~35 g·cm
  - Speed range: 0.22 m/s (min) – 0.71 m/s (max)  
  *(Note: 0.22 m/s is the robot's minimum effective speed; the motor itself can operate slower.)*

---

####  Motor Driver

- **L298N Dual H-Bridge Motor Driver**  
  The L298N module is used to control the DC and servo motors. It consists of:
  - An L298 integrated motor driver IC
  - A 78M05 5V regulator
  
  Features:
  - Can control up to 2 DC motors (direction + speed), but two in out car
  - Compatible with TTL logic levels (from Arduino UNO)

<p align="center">
  <img src="media/L298N_Dual_H_Bridge.jpg" alt="L298N Motor Driver" width="40%">
</p>

---

####  Distance and Motion Sensing

- **HC-SR04 Ultrasonic Sensors**  
  The robot uses **3 ultrasonic sensors** placed at the front, left, and right to detect obstacles and measure distances. Each sensor operates as follows:
  - Emits 8 ultrasonic pulses at 40kHz via the TRIG pin.
  - Detects reflected sound using the ECHO pin.
  - Measures time of flight to calculate distance (2–450 cm range).
  
  These sensors are not affected by sunlight or dark materials, but may struggle with acoustically soft surfaces (e.g., cloth or wool).

<p align="center">
  <img src="media/Ultrasonic_Sensors.png" alt="Ultrasonic Sensors" width="40%">
</p>

- **IMU Sensor (Inertial Measurement Unit)**  
  The robot includes an IMU sensor (e.g., MPU6050 or similar) that provides motion data through **gyroscope and accelerometer readings**. This allows:
  - Orientation tracking
  - Tilt detection
  - Smoother navigation control (especially in turns or uneven motion)

  The IMU is connected via I2C to the Arduino, which processes raw motion data or forwards it to the Raspberry Pi for sensor fusion and decision making.

<p align="center">
  <img src="media/Imu_Sensor.jpg" alt="IMU Sensor" width="40%">
</p>

---

####  Power Supply

- **Power bank**
  The power bank will be our main source for keeping the Raspberry PI charged, which will also give the arduino its charge

- **3x - 3.7 Li-Po**  
  The robot is powered using a **3x - 3.7 Li-** Po-- 4.2 Max ~= 12.6v on max , to enable the motor to receive power through the L298N driver module.

###  Coding Environments

The robot's software is developed using two main programming environments: **Arduino IDE (C++)** and **Python**. Each environment is responsible for different layers of control, from low-level motor actuation to high-level vision processing.

---


####  Arduino IDE (C++)

The **Arduino Integrated Development Environment (IDE)** is a cross-platform application (available for Windows, macOS, and Linux) used to program Arduino-compatible boards. Written in Java, the IDE supports both C and C++ languages with simplified structure requirements.

Key features:
- Provides built-in libraries for common I/O operations (based on the Wiring framework).
- Requires only two user-defined functions: `setup()` for initialization and `loop()` for continuous execution.
- Uses the GNU toolchain to compile code, and **AVRDUDE** to upload the hex-encoded binary to the board.

**Role in the project:**
- The Arduino IDE is used to program the **Arduino Uno**, which directly controls:
  - Rear-wheel drive motion
  - Steering through the servo motor
- These actions are performed based on movement commands received from the Raspberry Pi Camera (e.g., left/right turns or forward/backward motion).

---

####  Python

**Python** is a high-level, interpreted programming language known for its readability and flexibility.

**Role in the project:**
- Python runs on the **Raspberry Pi 5** and is responsible for:
  - **Camera input handling**
  - **Color and object detection**
  - **Sending motion commands** to the Arduino Uno based on visual analysis

**Libraries**
- OpenCV library will be used to detecet colors (RED, GREEN).



