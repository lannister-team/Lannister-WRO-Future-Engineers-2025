/*
Code Descreption: 
Main WRO_Car code (Adafruit MPU6050 version)

Code_Purpose:
The main one, what do you think it's purpose (:, do fries ?? ofc move the car

Game Mat Size:
🧩 Game Mat Size: 3000 mm × 3000 mm (approx. 2.36 m × 1.14 m) 
wroindia.org

📏 Allowed Tolerance: ± 5 mm in each direction

⬆️ Table Height/Borders: Built with 50 mm high borders to contain the mat 

CAR: 
30x20x30

Interior Square:
In Open Challenge rounds:
Corridor width can be either 600 mm or 1000 mm, ±100 mm tolerance 

In Obstacle Challenge rounds:
Corridor width is fixed at 1000 mm, ±10 mm tolerance 

*/

/*
▶️ Red = Pass from the left side.
▶️ Green = Pass from the right side.
*/

#include "camera_detect.h"
#include "moving.h"
#include "ultrasonic.h"
#include "imu.h"
#include "servo_motor.h"

#define GREEN_OBJECT 'G'
#define RED_OBJECT 'R'
#define NONE_OBJECT 'N'

#define LEFT_OBJECT 'L'
#define RIGHT_OBJECT 'R'
#define CENTER_OBJECT 'C'

// ======== IMU ========
sensors_event_t a, g, temp;
float turn_angle = 0;
unsigned long last_time = 0;
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 imu;
// ======== IMU ========

const int MAX_DISTANCE_FROM_WALL_FORWARD = 95;
const int MAX_DISTANCE_FROM_WALL_LEFT = 60;
const int MAX_DISTANCE_FROM_WALL_RIGHT = 60;
const int MIN_DISTANCE_FROM_WALL_LEFT = 30;
const int MIN_DISTANCE_FROM_WALL_RIGHT = 30;
const int MAX_DISTANCE_FROM_OBJECT = 20;

const int IMU_MAX_DIFFERENCE = 5;

const int MAX_DISTANCE_TO_BACK = 0;

void setup() {
  motor_setup();
  ultrasonic_setup();
  IMU_setup(imu);
  servo_setup();

  Serial.begin(9600);
}

/*
Outputs:
Servo Motor: Go angle
Motor: Move
*/



/*
R/G/N
area (NUMBER OF PXELS)
direction (L/R/C)
difference

IMU: 
Z



Inputs:
Camera: color, area, direction, difference    
IMU: tunr_angle
Ultrasonic: rd, ld, fd
Motor_encoder: distance moved
*/ 

void loop()
{
  // ============================== Camera Inputs ==============================
  String object = get_object();
  int firstColon = object.indexOf(':');
  int secondColon = object.indexOf(':', firstColon + 1);
  int thirdColon = object.indexOf(':', secondColon + 1);

  char object_color = object.charAt(0);
  int object_area = object.substring(firstColon + 1, secondColon).toInt();
  char object_direction = object.charAt(secondColon + 1);
  int object_difference = object.substring(thirdColon + 1).toInt();
  // ============================== Camera Inputs ==============================

  // ============================== IMU Inputs ==============================
  imu.getEvent(&a, &g, &temp);
  unsigned long now = millis();
  float dt = (now - last_time) / 1000.0;  // convert ms to seconds
  last_time = now;

  float gyro_z = g.gyro.z * 57.2958; // rad/s to °/s
  turn_angle += gyro_z * dt;

  // All IMU inputs
  // float imu_ax = a.acceleration.x / 9.81; // in g
  // float imu_ay = a.acceleration.y / 9.81;
  // float imu_az = a.acceleration.z / 9.81;

  // float imu_gx = g.gyro.x * 57.2958; // convert rad/s to °deg/s 
  // float imu_gy = g.gyro.y * 57.2958;
  // float imu_gz = g.gyro.z * 57.2958;
  // ============================== IMU Inputs ==============================

  // ============================== Ultrasonic Inputs ==============================
  /*
    #define LEFT_US 2
    #define RIGHT_US 0
    #define FRONT_US 1
  */

  float rd_ultrasonic = get_ultrasonic_output(trig_pins[RIGHT_US], echo_pins[RIGHT_US]);
  float ld_ultrasonic = get_ultrasonic_output(trig_pins[LEFT_US], echo_pins[LEFT_US]);
  float fd_ultrasonic = get_ultrasonic_output(trig_pins[FRONT_US], echo_pins[FRONT_US]);
  // ============================== Ultrasonic Inputs ==============================

  // ============================== Motor Inputs ==============================
  float total_distance = get_distance();
  // ============================== Motor Inputs ==============================

  print_inputs(object_color, object_area, object_direction, object_difference, turn_angle, rd_ultrasonic, ld_ultrasonic, fd_ultrasonic, total_distance);
  
  delay(100);
}

/*
#define GREEN_OBJECT 'G'
#define RED_OBJECT 'R'
#define NONE_OBJECT 'N'

#define LEFT_OBJECT 'L'
#define RIGHT_OBJECT 'R'
#define CENTER_OBJECT 'C'
*/

//                   object color  number of pixels     Left/Right/Center  how far from center    imu dimantions--------------------------------------------------------  ultrasonics data --------------------------------------------  total moved distance 
void get_inputs(char object_color, int object_area, char object_direction, int object_difference, float turn_angle, float rd_ultrasonic, float ld_ultrasonic, float fd_ultrasonic, float total_distance)
{

  // ====================================================================================================
  // if there's an obstacle front you
  if (object_color != NONE_OBJECT)
  {
    // if the object GREEN
    if (object_color == GREEN_OBJECT)
    {
      if (object_direction == LEFT_OBJECT)
      {
        // MOVE FORWARD
        move_forward();
        return_center();
        // Function for checking if there's hazarad
      }

      else if (object_direction == RIGHT_OBJECT || object_direction == CENTER_OBJECT)
      {
        // Will see the ultra sonic output (if i can turn)
        // if can't turn, MOVE BackWard **************************************************** (if no time to turn)
        if (fd_ultrasonic <= MAX_DISTANCE_FROM_OBJECT)
        {
          move_back();
        }

        // if can turn 
        // will turn according to the 1- C/R, 2- difference 
        else
        {
          move_forward();
          turn_right();
          if (turn_angle != -90)
          {
            set_servo_angle(150);
          }
        }

        // after turning, keep traking the IMU
        // Function for checking if there's hazarad
      }
    }

    // if the object RED
    else
    {
      if (object_direction == RIGHT_OBJECT)
      {
        // MOVE FORWARD
        // Function for checking if there's hazarad
        move_forward();
        return_center();
      }

      else if (object_direction == LEFT_OBJECT || object_direction == CENTER_OBJECT)
      {
        if (fd_ultrasonic <= MAX_DISTANCE_FROM_OBJECT)
        {
          move_back();
        }

        else
        {
          move_forward();
          turn_left();
          if (turn_angle != 90)
          {
            set_servo_angle(35);
          }
        }

        // Will see the ultra sonic output (if i can turn)
        // if can't turn, MOVE BackWard
        // if can turn 
        // will turn according to the 1- C/L, 2- difference 
        // after turning, keep traking the IMU
        // Function for checking if there's hazarad
      }
    }
    
  }
  // ====================================================================================================
  
  // If there's no obstacels
  else
  {
    move_forward();
    // MOVE FORWARD
    // Function for checking if there's hazarad

    // if it's time to turn
    if (fd_ultrasonic <= MAX_DISTANCE_FROM_WALL_FORWARD)
    {
      // Then it's ok to turn left
      if (ld_ultrasonic > MAX_DISTANCE_FROM_WALL_LEFT)
      {
        
        if (turn_angle != 90)
        {
          set_servo_angle(35);
        }

        else
        {
          turn_left();
        }
        // turn the servo 90 degree (left)
        // IMU Detect
      }

      // Then it's ok to turn right
      else if (rd_ultrasonic > MAX_DISTANCE_FROM_WALL_RIGHT)
      {

        if (turn_angle != 90)
        {
          set_servo_angle(150);
        }

        else
        {
          turn_right();
        }
        // turn the servo -90 degree (RIGHT)
        // IMU Detect
      }
    }
  }

}

/*
Inputs:
Camera: color, area, direction, difference
IMU: ax, ay, az, gx, gy, gz
Ultrasonic: rd, ld, fd
Motor_encoder: distance moved
*/ 

void print_inputs(char object_color, int object_area, char object_direction, int object_difference, float turn_angle, float rd_ultrasonic, float ld_ultrasonic, float fd_ultrasonic, float total_distance)
{
  Serial.print("Turn_Aangle: ");
  Serial.print(turn_angle);

  Serial.print("Ultrasonic: R: ");
  Serial.print(rd_ultrasonic);
  Serial.print(" F: ");
  Serial.print(fd_ultrasonic);
  Serial.print(" L: ");
  Serial.println(ld_ultrasonic);

  Serial.print("Toal Distance");
  Serial.println(total_distance);
  Serial.println();
  Serial.println("=====================================");
  Serial.println();
}
