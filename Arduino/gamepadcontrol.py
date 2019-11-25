import xbox
import serial

# ser = serial.Serial('/dev/ttyUSB0',115200)
joy = xbox.Joystick()
while True:
    (x, y) = joy.leftStick()
    command = chr(abs(int(y*255)))
    moving_forward = int(y > 0)
    if y == 0:
        direction = 0
    elif y > 0:
        direction = 2
    else:
        direction = 4
    command += chr(direction + moving_forward)
    command = command.encode('utf-8')
    print(type(command))
    # ser.write(command)
