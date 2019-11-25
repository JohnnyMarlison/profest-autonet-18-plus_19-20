import xbox
import serial

# ser = serial.Serial('/dev/ttyUSB0',115200)
joy = xbox.Joystick()
command = b'123'
while True:
    (x,y) = joy.leftStick()
    command = chr(int(abs(y * 255))) + chr(int(abs(x * 255))) + chr((int((y > 0)*2) + int(x > 0)))
    # ser.write(command.encode('utf-8'))
    print(command)
