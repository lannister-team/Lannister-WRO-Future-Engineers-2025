/*
Code Descreption: 
part of WRO_car code for arduino, Specifically for camera output givin to the arduino

Code_Purpose:
get the data from the camera through serial communication (9600)

*/



#include "./camera_detect.h"

String get_object()
{
  if (Serial.available())
  {

    String input = Serial.readStringUntil('\n');
    input.trim(); // to remove any extra spaces
    return input;
  }
  
  return "";   
}
