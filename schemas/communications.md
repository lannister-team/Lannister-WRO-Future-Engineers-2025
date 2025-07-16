## Communication Summary Table

A table for all communications protocol summary

| Component               | Connected To       | Communication Type / Protocol |
|-------------------------|--------------------|-------------------------------|
| Raspberry Pi Camera     | Raspberry Pi 5     | CSI (Camera Serial Interface) |
| Raspberry Pi 5          | Arduino Uno        | UART (Serial)                 |
| Ultrasonic Sensors (x3) | Arduino Uno        | Digital I/O (Trig/Echo)       |
| L298N H-Bridge          | Arduino Uno        | PWM + GPIO                    |
| DC Motor Encoder        | Arduino Uno        | Digital GPIO / Interrupt      |
| MPU6050 IMU             | Arduino Uno        | I2C (SDA/SCL)                 |
| Servo Motor             | Arduino Uno        | PWM                           |
| DC Motor                | L298N H-Bridge     | Direct Power Wires            |
