import cv2
import numpy as np

def color_detection_bgr_webcam():
    # Open the webcam
    cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)  # Use the default webcam

    if not cap.isOpened():
        print("Error: Could not open webcam.")
        return
    
    # Initialize trackbar window
    cv2.namedWindow("Trackbars", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("Trackbars", 640, 200)
    
    # Callback function for trackbars (does nothing, as OpenCV requires it)
    def empty(a):
        pass
    
    # Create trackbars for adjusting BGR ranges
    cv2.createTrackbar("Blue Min", "Trackbars", 0, 255, empty)
    cv2.createTrackbar("Blue Max", "Trackbars", 255, 255, empty)
    cv2.createTrackbar("Green Min", "Trackbars", 0, 255, empty)
    cv2.createTrackbar("Green Max", "Trackbars", 255, 255, empty)
    cv2.createTrackbar("Red Min", "Trackbars", 0, 255, empty)
    cv2.createTrackbar("Red Max", "Trackbars", 255, 255, empty)
    
    while True:
        # Capture frame from webcam
        ret, frame = cap.read()
        
        if not ret:
            print("Failed to grab frame")
            break
        
        # Get current positions of trackbars
        b_min = cv2.getTrackbarPos("Blue Min", "Trackbars")
        b_max = cv2.getTrackbarPos("Blue Max", "Trackbars")
        g_min = cv2.getTrackbarPos("Green Min", "Trackbars")
        g_max = cv2.getTrackbarPos("Green Max", "Trackbars")
        r_min = cv2.getTrackbarPos("Red Min", "Trackbars")
        r_max = cv2.getTrackbarPos("Red Max", "Trackbars")
        
        # Define the lower and upper bounds for the BGR mask
        lower = np.array([b_min, g_min, r_min])
        upper = np.array([b_max, g_max, r_max])
        
        # Create a mask that isolates the colors in the defined range
        mask = cv2.inRange(frame, lower, upper)
        
        # Show the original image and the mask
        cv2.imshow("Image", frame)
        cv2.imshow("Mask", mask)
        
        # Exit if the user presses 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    
    # Release the webcam and close all windows
    cap.release()
    cv2.destroyAllWindows()

# Run the function
color_detection_bgr_webcam()
