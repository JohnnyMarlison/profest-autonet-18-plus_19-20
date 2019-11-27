#!/usr/bin/env python
import sys, select, termios, tty
import rospy
from autokin_move_msg.msg import autokin_move_msg

#pressed_keys = {'w' : 0, 'a' : 0, 's' : 0, 'd' : 0, 'x' : 0}

def moving_direction(speed):
	if(speed < 0):
		return 0
	return 1

def getKey(settings):
    tty.setraw(sys.stdin.fileno())
    select.select([sys.stdin], [], [], 0)
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def talker():
    settings = termios.tcgetattr(sys.stdin)
    speed = 0
    moving_forward = 1
    turn = 0
    pub = rospy.Publisher('autokin_move', autokin_move_msg, queue_size=10)
    rospy.init_node('autokin_teleop_node')
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        key = getKey(settings)
        if(key == 'w'):
            if(speed <=245):
                speed +=10
        if(key == 's'):
            if(speed >= -245):
                speed -= 10
        if(key == 'a'):
            turn = 1
        elif(key == 'd'):
            turn = 2
        else:
            turn = 0
        if(key == 'x'):
            speed = 0
            turn = 0
        if(key == '\x03'):
            break
        moving_forward = moving_direction(speed)
        rospy.loginfo("{} {} {}".format(abs(speed), moving_forward, turn))
        pub.publish(abs(speed), moving_forward, turn)
        rate.sleep()
    pub.publish(0, 1, 0)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
#    finally:
#        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
