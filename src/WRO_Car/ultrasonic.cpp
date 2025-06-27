/*
Code Descreption: 
part of WRO_car code for arduino, Specifically for the ultrasonic sensors

Code_Purpose:
avoid any obstecle and know distances

Ultrasonic output:
Range	Reliability	Comment
0–200 cm	⭐⭐⭐⭐☆ (Good)	Flat, hard wall? Very reliable.
200–300 cm	⭐⭐☆☆☆ (OK-ish)	Might work, but noisy, especially on angle
300–400 cm	⭐☆☆☆☆ (Unreliable)	Weak echo, often false or no reading 

*/



#include "./ultrasonic.h"

void ultrasonic_setup()
{
  for (int i = 0 ; i < ULTRASONICS_NUMBERS ; i++)
  {
    pinMode(echo_pins[i], INPUT);
    pinMode(trig_pins[i], OUTPUT);
  }
}

float get_ultrasonic_output(int trig, int echo)
{
  digitalWrite(trig, 0); delay(2 / 1000); // low then high then low to trig the distance (small delay is required)
  digitalWrite(trig, 1); delay(2 / 1000);
  digitalWrite(trig, 0);

  long duration = pulseIn(echo, HIGH);
  return  duration * 0.034 / 2; // distance = speed * time (duration) ( /2 because the duration in for going and back for the sonic)

}

int is_close_object(int distance)
{
  for (int i = 0 ; i < ULTRASONICS_NUMBERS ; i++)
  {
      if (get_ultrasonic_output(trig_pins[i], echo_pins[i]) > distance)
        return i; // if there's an object, return it's distance (the priority to front ultra sonic)
  }

  return -1;
}



