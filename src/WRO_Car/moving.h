/*
Code Descreption: 
part of WRO_car code for arduino, specific for the motor and wheels movment

Code_Purpose:
move the car for any direction according to the main code observations

*/

#ifndef moving_h
#define moving_h

#include <Arduino.h>

const int motor_positive = 9, motor_negative = 8, ENA = 5;

const float wheelDiameter = 65.0; // mm
const int pulsesPerRevolution = 495; // PPR

const byte encoderPinA = 2; // encoder Channel A
const byte encoderPinB = 3; // encdoer chanel B



void motor_setup();
void set_speed(int);
void move_back();
void move_forward();
void stop();
float get_distance();
void countEncoder();

#endif