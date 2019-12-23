#include "AX12A.h"

#define DirectionPin    (10)
#define BaudRate        (57600)
#define MAX_ANGLE       (150)
#define BASIC_SPEED     (200)
#define COMMAND_LEN     (2)
#define LEFT_MOTOR_A    (4)
#define LEFT_MOTOR_B    (5)
#define RIGHT_MOTOR_A   (6)
#define RIGHT_MOTOR_B   (7)
#define FORWARD         (0)
#define BACKWARD        (1)

int     Cur_angle = 0,
        pos = 0,
        i = -150,
        com[COMMAND_LEN];

int step = 5;

void correct_position(int & pos) {
    pos = (pos < -MAX_ANGLE) ? -MAX_ANGLE : pos;
    pos = (pos > MAX_ANGLE) ? MAX_ANGLE : pos;
}

void turnAngle(int angle, int _speed = BASIC_SPEED) {
    Cur_angle = angle;
    correct_position(Cur_angle);
    ax12a.moveSpeed(1, static_cast <int> (512 + angle * 3.41), _speed);
}

void setup() 
{
     Serial.begin(9600);
    ax12a.begin(BaudRate, DirectionPin, &Serial2);
    ax12a.setEndless(1, OFF);
    turnAngle(0);
}

void drive(int speed)
{
    if(abs(speed) > 255) return;
    if (speed == 0) 
    {
        stop();
        return;
    }
    analogWrite(LEFT_MOTOR_A,   (speed > 0)?    0:abs(speed));
    analogWrite(LEFT_MOTOR_B,   (speed < 0)?    0:abs(speed));
    analogWrite(RIGHT_MOTOR_A,  (speed > 0)?    0:abs(speed));
    analogWrite(RIGHT_MOTOR_B,  (speed < 0)?    0:abs(speed));        
} 
void stop()
{
    analogWrite(LEFT_MOTOR_A,0);
    analogWrite(LEFT_MOTOR_B,0);
    analogWrite(RIGHT_MOTOR_A,0);
    analogWrite(RIGHT_MOTOR_B,0);
}


void loop()
{
  Serial.println(ax12a.readPosition(1));
  delay(1000);
  turnAngle(30);
  delay(500);
  Serial.println(ax12a.readPosition(1));
}




    // int speed_task, ang_task;
    // pos = ax12a.readPosition(1);
    // if (Serial.available() == COMMAND_LEN)
    // {
    //     for(uint8_t i = 0; i < COMMAND_LEN; i++)
    //     {
    //         com[i] = Serial.read();
    //     }
    // }
    // speed_task = com[0];
    // ang_task = com[1];
    // if(ang != pos)
    // {
    //     turnAngle(ang, BASIC_SPEED);
    // }
