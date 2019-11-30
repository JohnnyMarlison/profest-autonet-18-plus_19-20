#!/usr/bin/env python
import keyboard
import rospy
from autokin_move_msg.msg import autokin_move_msg

#pressed_keys = {'w' : 0, 'a' : 0, 's' : 0, 'd' : 0, 'x' : 0}

def moving_direction(speed):
	if(speed < 0):
		return 0
	return 1

#def on_press(key):
#    pressed_keys[key.char] = 1

#def on_release(key):
#    pressed_keys[key.char] = 0

def talker():
    speed = 0
    moving_forward = 1
    turn = 0
    pub = rospy.Publisher('autokin_move', autokin_move_msg, queue_size=10)
    rospy.init_node('autokin_teleop_node')
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        if(keyboard.is_pressed('w')):
            if(speed <=245):
                speed +=10
        if(keyboard.is_pressed('s')):
            if(speed >= -245):
                speed -= 10
        if(keyboard.is_pressed('a')):
            turn = 1
        elif(keyboard.is_pressed('d')):
            turn = 2
        else:
            turn = 0
        if(keyboard.is_pressed('x')):
            speed = 0
            turn = 0
        moving_forward = moving_direction(speed)
        rospy.loginfo("{} {} {}".format(abs(speed), moving_forward, turn))
        pub.publish(abs(speed), moving_forward, turn)
        rate.sleep()


if __name__ == '__main__':
#    listener = keyboard.Listener(
#        on_press=on_press,
#        on_release=on_release)
#    listener.start()
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
