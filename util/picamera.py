import cv2
import imutils
import numpy as np
from picamera.array import PiRGBArray
from picamera import PiCamera

# Path to the haarcascade_frontalface_default.xml file
face_cascade_path = '/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml'

# Load the cascade classifier file
face_cascade = cv2.CascadeClassifier(face_cascade_path)
if face_cascade.empty():
    print("Failed to load cascade classifier file")
    exit()

# Initialize the PiCamera object with resolution of 320x240 pixels and a framerate of 32 frames per second
camera = PiCamera()
camera.resolution = (320, 240)
camera.framerate = 32

# Create a PiRGBArray object to store a sequence of images
raw_capture = PiRGBArray(camera, size=(320, 240))

# Create a CascadeClassifier object to detect faces
face_cascade = cv2.CascadeClassifier(face_cascade_path)

try:
    # Continuously capture frames from the camera
    for frame in camera.capture_continuous(raw_capture, format="bgr", use_video_port=True):
        # Get the current image from the camera
        image = frame.array

        # Convert the image to grayscale
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        # Detect faces in the grayscale image using the CascadeClassifier
        faces = face_cascade.detectMultiScale(
            gray,
            scaleFactor=1.1,
            minNeighbors=5,
            minSize=(30, 30),
            flags=cv2.CASCADE_SCALE_IMAGE
        )

        # Draw a green rectangle around each detected face
        for (x, y, w, h) in faces:
            cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)

        # Display the image on the screen
        cv2.imshow("Frame", image)

        # Wait for a key press to exit
        key = cv2.waitKey(1) & 0xFF

        # Exit the program if the 'q' key is pressed
        if key == ord("q"):
            break

        # Clear the buffer in preparation for the next frame
        raw_capture.truncate(0)

# Clean up resources if the program is interrupted by the user
except KeyboardInterrupt:
    cv2.destroyAllWindows()
    print("\nClosing program and cleaning up resources... Goodbye!")
