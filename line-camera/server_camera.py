import time
import cv2
import numpy as np
import re
import socket

# add settings for stream
TCP_PORT_VIDEO = 9000
sock_video = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock_video.bind(('', TCP_PORT_VIDEO))
sock_video.listen(1)
conn_video, addr = sock_video.accept()
print('Video connected')
prev = 0
frame_rate = 15

cap = cv2.VideoCapture(0)

print('Camera connected')

while(True):
	ret, frame = cap.read()	
	
	time_elapsed = time.time() - prev
	if (time_elapsed > 1./frame_rate):
		image = frame.array
		prev = time.time()
		encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 90]
		data = np.array(imencode)
		stringData = data.tostring()
		print("start translate: ", len(stringData))

		if (len(stringData) > 10000):
			conn_video.send(str(len(stringData)).encode())
			conn_video.send(stringData)
	
	# Press Q on keyboard to stop recording
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

# Closes all the frames
cap.release()
cv2.destroyAllWindows()

