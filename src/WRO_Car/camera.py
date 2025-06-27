"""

Code Descreption: 
the main code (and the only) for the raspberry PI camera using python

Code_Purpose:
to detect red and green obstecales in the track then send serial data to the arduino according
to the observations

Libraries:
open_CV: to detect colors and extract shapes
serial: to comminicate with the arduino
picamera2: to get the data from the PI camera (module v3)
numpy: efficient way to deal with arrays
time: to do delays when needed


"""


import cv2
import numpy as np
from picamera2 import Picamera2
import time
import serial

# start serial communication
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

# get the camera
picam2 = Picamera2()

# Set the window size, make BGR format
video_config = picam2.create_video_configuration(
    main={"size": (640, 480), "format": "BGR888"}
)
# imply the configurations
picam2.configure(video_config)

picam2.start()  # start the camera
time.sleep(1)   # give the camera time to warm up

# will create a 5X5 array of 1's, which is the minimum required to consider as shape
kernel = np.ones((5, 5), np.uint8)

print("Press 'q' to quit.")

# detect and return image + mask + color
def detect_colors():
    frame_pil = picam2.capture_image("main")  # capture the photo
    frame = np.array(frame_pil.convert("RGB"))  # convert the photo to RGB formate
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)  # Convert from RGB to OpenCV format (BGR)

    # Convert to HSV format
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # HSV range for red
    lower_red1 = np.array([0, 100, 100])
    upper_red1 = np.array([10, 255, 255])
    lower_red2 = np.array([160, 100, 100])
    upper_red2 = np.array([179, 255, 255])

    # HSV range for green
    lower_green = np.array([40, 70, 70])
    upper_green = np.array([85, 255, 255])

    # Masks for green and red (consider red/green white - other bits as black)
    mask1 = cv2.inRange(hsv, lower_red1, upper_red1)
    mask2 = cv2.inRange(hsv, lower_red2, upper_red2)
    red_mask = cv2.bitwise_or(mask1, mask2)
    green_mask = cv2.inRange(hsv, lower_green, upper_green)

    # ignore the shapes that are not in 5x5 range
    red_mask = cv2.morphologyEx(red_mask, cv2.MORPH_OPEN, kernel)
    green_mask = cv2.morphologyEx(green_mask, cv2.MORPH_OPEN, kernel)

    # find contours and use shape + area to detect valid objects
    def detect_color_from_mask(mask):
        # extracts the edges of white blobs in the mask.
        # RETR_EXTERNAL: only detects outermost contours (ignores holes inside shapes).
        # CHAIN_APPROX_SIMPLE: compresses points to reduce memory usage.
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        for cnt in contours:
            # Calculates the area in pixels of the shape. Small areas are usually noise or far objects.
            area = cv2.contourArea(cnt)
            if area < 2000:  # filter out small noise
                continue

            # detect a polygon shape
            approx = cv2.approxPolyDP(cnt, 0.04 * cv2.arcLength(cnt, True), True)
            if len(approx) >= 4:  # square or blob-like
                x, y, w, h = cv2.boundingRect(cnt)
                aspect_ratio = w / float(h)
                if 0.6 < aspect_ratio < 1.4:  # roughly square/rectangle
                    return True
        return False

    if detect_color_from_mask(red_mask):
        return frame, red_mask, green_mask, "RED"
    elif detect_color_from_mask(green_mask):
        return frame, red_mask, green_mask, "GREEN"

    return frame, red_mask, green_mask, "NONE"


def main():
    green_flag, red_flag, none_flag = False, False, False

    while True:
        # detect colors and return masks for display
        frame, red_mask, green_mask, data = detect_colors()

        # pop up a window to show the masks
        cv2.imshow("Camera View", frame)
        cv2.imshow("Red Mask", red_mask)
        cv2.imshow("Green Mask", green_mask)

        # when 'q', exit
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        if data == "GREEN":
            if green_flag:
                continue
            ser.write(b'G')
            green_flag = True
            none_flag, red_flag = False, False
            print("GREEN")

        elif data == "RED":
            if red_flag:
                continue
            ser.write(b'R')
            red_flag = True
            green_flag, none_flag = False, False
            print("RED")

        else:
            if none_flag:
                continue
            ser.write(b'N')
            none_flag = True
            green_flag, red_flag = False, False
            print("None")


if __name__ == '__main__':
    try:
        main()
    finally:
        # clean after finish
        ser.close()
        cv2.destroyAllWindows()
