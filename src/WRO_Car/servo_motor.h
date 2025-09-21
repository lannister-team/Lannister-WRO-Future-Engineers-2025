/*
Code Descreption: 
part of WRO_car code for arduino, Specifically for Servo motor and Stering control

Code_Purpose:
decide to move the stering (srvo motor) left or right or keep still based on camera, IMU and other inputs

*/

#ifndef servo_motor_h
#define servo_motor_h

#include <Wire.h>
#include <Arduino.h>
#include <Servo.h>
#include "moving.h"

const int SERVO_PIN = 12;
const int CENTER_ANGLE = 45;
const int LEFT_ANGLE = 45;
const int RIGHT_ANGLE = 135;

#define SERVO_DELAY 14
#define TURNINNG_DELAY 600

void servo_setup();
void set_servo_angle(int);
void turn_left();
void turn_right();
void return_center();
void move_for_angle(int *, int, int);

#endif