How we tuned our sensors
Tuning & Calibration (Ultrasonic • IMU • Servo)

This vehicle didn’t work “out of the box.” We spent a lot of time tuning three pieces that control stability and decisions: the **steering servo**, the **ultrasonic sensors**, and the **IMU**. Below is how we approached each one and what we learned.

---

### 1) Steering Servo — center, left, right

**Goal**
- Find the exact **center angle** for straight driving, and the **left/right angles** for safe, consistent turns without over-steer.

**What we did**
- Locked the car on a flat surface and **swept the servo** in small steps to see when wheels actually point straight.
- Set an initial **CENTER** angle, then measured turning radius to define **LEFT_MAX** and **RIGHT_MAX** that do not hit mechanical limits.
- Added a small **dead-band** so tiny IMU noise doesn’t cause jitter.
- Limited the **rate of change** (deg/s) so turns are smooth.

**Problems we hit**
- The horn alignment and gear **backlash** made “90° = straight” false.  
- Jitter from power noise → solved by giving the servo **separate 6 V rail with regulator** and common GND.
- Over-steer at high speed → fixed with **rate limiting** and smaller target angles.

**Final parameters (example)**
- `CENTER_ANGLE = 65°`  
- `LEFT_MAX = 0°`, `RIGHT_MAX = 90°`  
- `DEAD_BAND = ±1°`  
- `MAX_STEER_RATE = 180°/s`  
these are a starting point we reached after many trials.

### 2) Ultrasonic Sensors — distances & turn trigger

**Goal**
- Reliable distance reading to decide **when to trigger a turn** and **which side** is safer.

**What we did**
- Calibrated each sensor against known distances (20, 30, 40, 60 cm).
- Used **median/average of N samples** to fight noise.  
- Staggered triggers (few ms apart) to reduce **cross-talk** between sensors.
- Defined thresholds:
  - **Front stop/turn trigger** (when to stop trying to go straight).
  - **Side clearance** (minimum safe space to pick a side).
  - **Side margin** (how much one side must beat the other).

**Problems we hit**
- Cross-talk gave random spikes → **inter-sensor delays** helped.  
- Narrow FOV misalignment → we re-angled the brackets slightly outward.  
- Glossy surfaces returning bad echoes → we average more samples near shiny objects.


**Decision rule (no camera)**
- If `front < FRONT_TURN_TRIG_CM`:  
  - Compare `left` vs `right`.  
  - Choose the side with **greater distance** by at least `SIDE_MARGIN_CM`.  
  - If tie, we **prefer right** (configurable).  
  - If neither side ≥ `SIDE_CLEAR_CM` → **STOP**.

---

### 3) IMU (MPU6050) — keep it straight

**Goal**
- Use the IMU to **hold a straight heading** and gently correct drift without oscillations.

**What we did**
- Performed **gyro/accel offset calibration** at startup (vehicle still).  
- Fused gyro+accel with a **complementary/low-pass filter** to reduce noise.  
- Defined **target heading** at the moment we start moving straight.  
- Applied **PID control** on the heading error to generate small steering corrections.
- Added **integral wind-up guard** and **output clamp** to avoid over-correction.

**Problems we hit**
- Drift over time → improved with better calibration and a gentle filter (not too slow).  
- Vibration coupling into the IMU → we **soft-mounted** the board and reduced motor PWM ripple.  
- Noise causing servo twitch → the **dead-band** and PID tuning fixed it.


**Control loop idea**
- Error = `target_heading − current_heading`  
- Servo correction = `PID(error)`  
- Apply correction only if `|error| > DEAD_BAND`

---

