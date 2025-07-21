##  Obstacles Detecting

The obstacle detection system is implemented using **Python**, running on a **Raspberry Pi** with a **Pi Camera v3**. The main goal is to identify **red** and **green** obstacles placed on the track and send their status to the Arduino for real-time driving decisions.

###  Code Purpose

The `camera.py` script continuously captures frames, detects the presence of red or green colored shapes using **OpenCV**, and sends a single-character signal (`'R'`, `'G'`, or `'N'`) over **serial communication** to the Arduino.

---

###  Libraries Used

| Library        | Role                                                                |
|----------------|---------------------------------------------------------------------|
| `OpenCV (cv2)` | For image processing and color detection                            |
| `picamera2`    | For accessing and configuring the Raspberry Pi camera               |
| `numpy`        | Efficient handling of image arrays                                  |
| `serial`       | Sending obstacle detection signals to Arduino via USB               |
| `time`         | Introduce delays and warm-up periods                                |

---

###  How It Works

#### 1. **Camera Setup**
- The camera is initialized using `picamera2` and configured to capture video at **640x480 resolution** in BGR format.
- A short `sleep(1)` delay is used to let the camera stabilize before processing starts.

#### 2. **Frame Processing**
Each captured frame goes through the following steps:

1. **Color Conversion**
   - Frame is converted from BGR to **HSV** color space.
   - HSV is preferred for color detection because it separates intensity (brightness) from color (hue), making it more robust under different lighting.

2. **Color Masking**
   - Two HSV ranges for red are used (`[0-10]` and `[160-179]`) because red wraps around the HSV hue circle.
   - One range for green (`[40–85]`) is sufficient.
   - `cv2.inRange()` is used to create binary masks (white for detected color, black for everything else).

3. **Morphological Filtering**
   - A **5×5 kernel** is used with `cv2.morphologyEx()` to eliminate noise (remove small dots or gaps in the mask).

4. **Contour Detection**
   - Contours are extracted from each mask using `cv2.findContours()`.
   - For each contour:
     - **Area filtering** ignores shapes with an area less than **2000 px** (to skip small/noisy objects).
     - **Shape approximation** checks that the object is blob-like or squarish (using aspect ratio filter `0.6 < AR < 1.4`).

5. **Color Decision**
   - If a red shape is detected → send `'R'`
   - If a green shape is detected → send `'G'`
   - If no valid shape is detected → send `'N'`

6. **Debouncing Signals**
   - Flags like `green_flag`, `red_flag`, and `none_flag` prevent resending the same character repeatedly unless a new object is detected.

7. **Visualization (Optional)**
   - Camera frame, red mask, and green mask are displayed in real time for debugging using OpenCV's `imshow`.

---

### Why These Hyperparameters?

| Parameter                     | Value           | Why Chosen                                                                 |
|------------------------------|------------------|-----------------------------------------------------------------------------|
| Frame size                   | `640x480`         | Standard resolution: good balance of performance and accuracy               |
| Red HSV range                | `[0-10] & [160-179]` | Red wraps around hue circle in HSV                                        |
| Green HSV range              | `[40–85]`         | Matches typical green object shades in WRO challenges                      |
| Area threshold               | `2000 px`         | Filters out tiny shapes and noise                                          |
| Morph kernel size            | `5×5`             | Enough to clean up small noise without destroying object shape             |
| Aspect Ratio (AR) Range      | `0.6 – 1.4`       | Detects rectangles or blobs, avoids lines or skewed shapes                 |
| Serial Baud Rate             | `9600`            | Matches Arduino’s UART speed for stable communication                      |

---

###  Output to Arduino

| Color Detected | Signal Sent |
|----------------|-------------|
| Green          | `'G'`       |
| Red            | `'R'`       |
| None           | `'N'`       |

Arduino reads this serial data using `Serial.readStringUntil('\n')` and processes it to decide how the car should move.
