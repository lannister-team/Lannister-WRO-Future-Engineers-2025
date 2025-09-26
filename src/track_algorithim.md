# Track Algorithim
this section for explaining the algorithim used in the Arduino files to win the track
🚗 Navigation Algorithm

The car’s navigation system combines data from the IMU, Ultrasonic Sensors, and the Camera to make real-time driving decisions.

1. Forward Motion with IMU Correction

By default, the car moves forward in a straight line.

The IMU (MPU6050) constantly monitors orientation (yaw/pitch).

If the car tilts left or right, the system calculates the deviation.

A correction command is sent to the steering servo motor to bring the wheels back to the center and maintain a straight path.

2. Obstacle Detection using Camera

The Raspberry Pi Camera is used to detect the color of obstacles or markers in front of the car:

Red → The car must avoid the obstacle by turning right.

Green → The car must overtake by moving to the left.

3. Safety Check with Ultrasonic Sensors

Three ultrasonic sensors are used: one at the front, one on the left, and one on the right.

When the camera detects an obstacle (red or green):

The system checks the ultrasonic sensor on the chosen side (right for red, left for green).

If the distance is safe (greater than a threshold), the car proceeds to turn.

If the distance is too small (blocked by a wall or another object), the car will stop to avoid collision.

4. Realignment after Maneuver

After completing a right or left maneuver:

The car uses IMU feedback again to stabilize the direction.

The steering servo returns to the corrected angle to continue driving straight.

🔑 Summary of Logic

Drive forward and use IMU to stay straight.

If the camera sees:

Red → Turn Right (if right side is clear).

Green → Overtake Left (if left side is clear).

Use ultrasonic sensors to confirm the side is free before turning.

If the side is blocked, the car stops.

After turning, the IMU realigns the car to continue straight.

This approach ensures:

Stability from the IMU.

Safety from the ultrasonic sensors.

Decision-making from the camera.
