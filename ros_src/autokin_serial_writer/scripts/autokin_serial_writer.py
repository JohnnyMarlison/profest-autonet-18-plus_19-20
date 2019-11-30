#!/usr/bin/env python
import serial
import rospy
from autokin_move_msg.msg import autokin_move_msg

def callback(data, ser):
    command = bytearray([data.speed, ((data.turn << 1) | data.moving_forward)])
#    rospy.loginfo(command[0], command[1])
    print(command)
    ser.write(command)

def writer():
    ser = serial.Serial('/dev/ttyUSB0', 115200)
    rospy.init_node('autokin_serial_writer', anonymous=True)
    rospy.Subscriber("autokin_move", autokin_move_msg, callback, ser)
    rospy.spin()

if __name__ == '__main__':
    writer()
