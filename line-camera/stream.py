import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while(True):
 	ret, frame = cap.read()

    # Display the resulting frame
   	cv2.imshow("Stream", frame)

    # Press Q on keyboard to stop recording
   	if cv2.waitKey(1) & 0xFF == ord('q'):
     		break

# When everything done, release the video capture and video write objects
cap.release()
 
# Closes all the frames
cv2.destroyAllWindows()
