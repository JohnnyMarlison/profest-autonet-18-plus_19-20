import cv2
import numpy as np

def nothing(x):
    pass

cap = cv2.VideoCapture(0)

cv2.namedWindow('Result')

cv2.createTrackbar('min_blue', 'result', 0, 255, nothing)
cv2.createTrackbar('min_green', 'result', 0, 255, nothing)
cv2.createTrackbar('min_red', 'result', 0, 255, nothing)

cv2.createTrackbar('max_blue', 'result', 0, 255, nothing)
cv2.createTrackbar('max_green', 'result', 0, 255, nothing)
cv2.createTrackbar('max_red', 'result', 0, 255, nothing)

#color = cv2.imread('color.jpg')

while (True):
    ret, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    cv2.imshow("hsv", hsv)

    min_blue = cv2.createTrackbar('min_blue', 'result', 0, 255, nothing)
    min_green = cv2.createTrackbar('min_green', 'result', 0, 255, nothing)
    min_red = cv2.createTrackbar('min_red', 'result', 0, 255, nothing)

    max_blue = cv2.createTrackbar('max_blue', 'result', 0, 255, nothing)
    max_green = cv2.createTrackbar('max_green', 'result', 0, 255, nothing)
    max_red = cv2.createTrackbar('max_red', 'result', 0, 255, nothing)


    mask = cv2.inRange(hsv, (min_blue, min_green, min_red), (max_blue, max_green, max_red))
    cv2.imshow('mask1', mask)

    result = cv2.bitwise_and(hsv, hsv, mask = mask)
    cv2.imshow('Result1', result)

    #mask2 = cv2.inRange(color, (min_blue, min_green, min_red), (max_blue, max_green, max_red))
    #cv2.imshow('Mask2', frame)

    #result2 = cv2.bitwise_and(color, frame, mask=mask)
    #cv2.imshow('Result2', frame)

    # Display the resulting frame
    #cv2.imshow("Stream", frame)

    # Press Q on keyboard to stop recording
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the video capture and video write objects
cap.release()

# Closes all the frames
cv2.destroyAllWindows()
