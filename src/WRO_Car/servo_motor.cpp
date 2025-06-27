/*
Code Descreption: 
part of WRO_car code for arduino, Specifically for Servo motor and Stering control

Code_Purpose:
decide to move the stering (srvo motor) left or right or keep still based on camera, IMU and other inputs

*/

#include "./servo_motor.h"
Servo steeringServo;

void servo_setup()
{
  steeringServo.attach(SERVO_PIN); // pin 12
  steeringServo.write(CENTER_ANGLE); // start from the center
}

void set_servo_angle(int angle)
{
  steeringServo.write(angle); // write the given angle to the servo motor
}

void turn_right()
{
  steeringServo.write(RIGHT_ANGLE);
}


void turn_left()
{
  steeringServo.write(LEFT_ANGLE);
}

void return_center()
{
  steeringServo.write(CENTER_ANGLE);
}