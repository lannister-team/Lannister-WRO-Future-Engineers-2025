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

#include "imu.h"

void IMU_setup(Adafruit_MPU6050 &imu)
{
  Wire.begin();

  if (!imu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  imu.setAccelerometerRange(MPU6050_RANGE_2_G);
  imu.setGyroRange(MPU6050_RANGE_250_DEG);
  imu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 Initialized with Adafruit Library");
}
