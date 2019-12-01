import cv2

def nothing(x):
    pass

cap = cv2.VideoCapture(-1)

cv2.namedWindow('result')

cv2.createTrackbar('min_blue', 'result', 0, 255, nothing)
cv2.createTrackbar('min_green', 'result', 0, 255, nothing)
cv2.createTrackbar('min_red', 'result', 0, 255, nothing)

cv2.createTrackbar('max_blue', 'result', 0, 255, nothing)
cv2.createTrackbar('max_green', 'result', 0, 255, nothing)
cv2.createTrackbar('max_red', 'result', 0, 255, nothing)

color = cv2.imread('color.jpg')

while (True):
    ret, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    cv2.imshow("hsv", hsv)

    min_blue = cv2.getTrackbarPos('min_blue', 'result')
    min_green = cv2.getTrackbarPos('min_green', 'result')
    min_red = cv2.getTrackbarPos('min_red', 'result')

    max_blue = cv2.getTrackbarPos('max_blue', 'result')
    max_green = cv2.getTrackbarPos('max_green', 'result')
    max_red = cv2.getTrackbarPos('max_red', 'result')

    hsv = cv2.blur(hsv, (5, 5))

    mask = cv2.inRange(hsv, (min_blue, min_green, min_red), (max_blue, max_green, max_red))
    cv2.imshow('mask', mask)

    result = cv2.bitwise_and(frame, frame, mask = mask)
    cv2.imshow('result', result)



    # Press Q on keyboard to stop recording
    # if cv2.waitKey(1) & 0xFF == ord('q'):
    #     break
    if cv2.waitKey(1) == 27:
        break

cap.release()
cv2.destroyAllWindows()
