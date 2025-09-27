# Track Algorithim
this section for explaining the algorithim used in the Arduino files to win the track
##  Navigation Algorithm

The car’s navigation system combines data from the **IMU**, **Ultrasonic Sensors**, and the **Camera** to make real-time driving decisions.  

---

### 1. Forward Motion (IMU Correction)
- The car drives forward by default.  
- The **IMU (MPU6050)** continuously monitors orientation (yaw/pitch).  
- If the car drifts left or right:  
  - The system calculates the deviation.  
  - The **steering servo motor** adjusts the wheel angle to realign the car.  

---

### 2. Camera-Based Obstacle Detection
- The **Raspberry Pi Camera** identifies the color of the obstacle ahead:  
  - **Red →** The car avoids the obstacle by turning **right**.  
  - **Green →** The car overtakes by moving to the **left**.  

---

### 3. Ultrasonic Safety Check
- Three **ultrasonic sensors** are used: **front, left, and right**.  
- When the camera detects an obstacle:  
  - The system checks the corresponding ultrasonic sensor:  
    - **Red →** Check the **right sensor**.  
    - **Green →** Check the **left sensor**.  
  - If the chosen side is clear (distance above threshold), the car proceeds with the maneuver.  
  - If blocked, the car will **stop** to prevent collision.  

---

### 4. Realignment After Maneuver
- After completing a turn (right or left):  
  - The **IMU feedback** is used again to stabilize the direction.  
  - The **servo motor** returns the wheels to the corrected forward position.  

---

###  Summary of Logic
1. Drive forward and keep straight using the **IMU**.  
2. If the camera detects an obstacle:  
   - **Red → Turn Right** (if right side is clear).  
   - **Green → Overtake Left** (if left side is clear).  
3. Use **ultrasonic sensors** to ensure the chosen side is free.  
4. If blocked, **stop**.  
5. After turning, use **IMU correction** to continue straight.  

---

This algorithm ensures:  
- **Stability** through IMU correction.  
- **Safety** with ultrasonic distance checks.  
- **Smart decision-making** using camera color detection.  
