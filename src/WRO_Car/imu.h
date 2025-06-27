/*
Code Descreption: 
part of WRO_car code for arduino, Specifically for IMU and space detection

Code_Purpose:
get the data from the IMU through I2C communication (A4, A5)
*/

/*
📦 1. 3-Axis Accelerometer → Measures Acceleration (in g or m/s²)
X-axis: Side-to-side acceleration (left/right)
Y-axis: Forward-backward acceleration
Z-axis: Up-down acceleration (gravity affects this too)

📦 2. 3-Axis Gyroscope → Measures Angular Velocity (in °/s or rad/s)
X-axis (Roll): Rotation around the side-to-side axis (like tilting your head sideways)
Y-axis (Pitch): Rotation around the front-back axis (like nodding "yes")
Z-axis (Yaw): Rotation around the vertical axis (like shaking your head "no")
*/

#ifndef imu_h
#define imu_h

#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

void IMU_setup(Adafruit_MPU6050 &imu);

#endif
