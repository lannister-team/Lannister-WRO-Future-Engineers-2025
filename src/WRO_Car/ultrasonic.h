/*
Code Descreption: 
part of WRO_car code for arduino, Specifically for the ultrasonic sensors

Code_Purpose:
avoid any obstecle and know distances

*/

#ifndef ultrasonic_h
#define ultrasonic_h

#include <Arduino.h>

#define LEFT_US 2
#define RIGHT_US 0
#define FRONT_US 1


const int echo_pins [3] = {A2, A1, A0}; // all echo pins for three ultrasonics
const int trig_pins [3] = {4, 7, 13}; // all trig pins for three ultrasonics
const int ULTRASONICS_NUMBERS = 3;

void ultrasonic_setup();
float get_ultrasonic_output(int trig, int echo);
int is_close_object(int distance);


#endif