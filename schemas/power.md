# Power

## Power Summary Table

A table for all components power summary

| Component               | Powered By         | Voltage       |
|-------------------------|--------------------|---------------|
| Raspberry Pi 5          | Powerbank          | 5V (USB-C)    |
| Raspberry Pi Camera     | Raspberry Pi 5     | 3.3V / Internal|
| Arduino Uno             | Raspberry Pi 5     | 5V (via USB)  |
| Ultrasonic Sensors (x3) | Arduino Uno        | 5V            |
| L298N H-Bridge          | External Battery   | 3X (3.7 Li-Ion)|
| DC Motor                | L298N H-Bridge     | 3X (3.7 Li-Ion)|
| DC Motor Encoder        | Arduino Uno        | 5V            |
| MPU6050 IMU             | Arduino Uno        | 5V (I2C)      |
| Servo Motor             | Arduino Uno        | 5V            |
