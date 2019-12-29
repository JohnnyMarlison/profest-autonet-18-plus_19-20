import keyboard
import serial

dir = [128, 0]
ser = serial.Serial('/dev/ttyUSB0', 9600)

while True:
    if keyboard.is_pressed('w'):
        dir[0] = 255
    if keyboard.is_pressed('a'):
        dir[1] = 0
    if keyboard.is_pressed('s'):
        dir[0] = 0
    if keyboard.is_pressed('d'):
        dir[1] = 60
    if keyboard.is_pressed('Space'):
        dir[0] = 128
        dir[1] = 30
    if keyboard.is_pressed('Esc'):
        break
    ser.write(bytearray(dir))
    
    