/*
Code Descreption: 
part of WRO_car code for arduino, specific for the motor and wheels movment

Code_Purpose:
move the car for any direction according to the main code observations

*/
volatile long encoderCount = 0;  // counts encoder pulses

#include "./moving.h"

    // Serial.print("Pulses: "); Serial.print(encoderCount);
    // Serial.print("  | Distance: "); Serial.print(distance_mm);
    // Serial.println(" mm");

void motor_setup()
{
  pinMode(motor_positive, OUTPUT);
  pinMode(motor_negative, OUTPUT);

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), countEncoder, RISING); // interrupt to count the distance efficiently
  move_forward();
}

float get_distance()
{
  float revolutions = encoderCount / (float)pulsesPerRevolution; // revolutions = encoderCount / pulsesPerRevolution
  return revolutions * (wheelDiameter * PI); // distance in mm , distance = revolutions * (wheelDiameter * PI)
}

void move_back()
{
  digitalWrite(motor_positive, 0);
  digitalWrite(motor_negative, 1);
}

void move_forward()
{
  digitalWrite(motor_positive, 1);
  digitalWrite(motor_negative, 0);
}

void stop()
{
  digitalWrite(motor_positive, 0);
  digitalWrite(motor_negative, 0);
}

void countEncoder() {
  encoderCount++;
}
