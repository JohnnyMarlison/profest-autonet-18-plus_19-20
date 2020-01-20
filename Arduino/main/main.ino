#include "AX12A.h"

#define DirectionPin    (10)
#define BaudRate        (57600)
#define MAX_POSITION    (30)
#define BASIC_SPEED     (150)
#define COMMAND_LEN     (2)
#define LEFT_MOTOR_A    (A0)
#define LEFT_MOTOR_B    (A1)
#define RIGHT_MOTOR_A   (A2)
#define RIGHT_MOTOR_B   (A3)
#define FORWARD         (0)
#define BACKWARD        (1)
#define ID              (1)
#define TIMEOUT         (100)
#define ZERO            (480)

int pos;
int turn_angle = 0;

    void setPos(int _pos = 0)
    {
        _pos *= -1;
        if (_pos  > MAX_POSITION)
        {
            pos = static_cast <int> (ZERO + 3.41 * MAX_POSITION);
        }
        else if (_pos < - MAX_POSITION)
        {
            pos = static_cast <int> (ZERO - 3.41 * MAX_POSITION);
        }
        else
        {
            pos = static_cast <int> (ZERO + 3.41 * _pos);
        }
    }

    int getPos()
    {
        return ax12a.readPosition(ID);
    }

    void turn()
    {
        int timestamp = millis();
        while (pos != getPos())
        {
            ax12a.moveSpeed(ID, pos, BASIC_SPEED);
            delay(25);
            if(millis() - timestamp >= TIMEOUT) return;
        }
    }
    void set_and_turn(int _pos = 0)
    {
      turn_angle += _pos;
      if (turn_angle > 20) turn_angle = 20;
      if (turn_angle < -20) turn_angle = -20;
      setPos(turn_angle);
      turn();
    }

char com = 'S';

void setup() 
{
  
    ax12a.begin(BaudRate, DirectionPin, &Serial2);
    ax12a.setEndless(ID, OFF);
    pos = 0;
    Serial3.begin(9600);
    set_and_turn(0);
    pinMode(13,OUTPUT);
}

void drive(int speed = 190)
{
    if(abs(speed) > 255) return;
    if (speed == 0) 
    {
        stop();
        return;
    }
    analogWrite(LEFT_MOTOR_A,   (speed > 0)?    0:abs(speed));
    analogWrite(LEFT_MOTOR_B,   (speed < 0)?    0:abs(speed));
    analogWrite(RIGHT_MOTOR_A,  (speed < 0)?    0:abs(speed));
    analogWrite(RIGHT_MOTOR_B,  (speed > 0)?    0:abs(speed));        
} 
void stop()
{
    analogWrite(LEFT_MOTOR_A,0);
    analogWrite(LEFT_MOTOR_B,0);
    analogWrite(RIGHT_MOTOR_A,0);
    analogWrite(RIGHT_MOTOR_B,0);
}

int time_recive = 1000, time_notrecive;

void loop()
{
    if (Serial3.available() > 0)
    {
      time_recive = millis();
      com = Serial3.read();
        switch(com)
        {
          case 'S':
            stop();
            break;
          case 'F':
            drive();
            break;
          case 'L':
            set_and_turn(2);
            break;
          case 'R':
            set_and_turn(-2);
            break;
          case 'B':
            drive(-190);
            break;
          case 'W':
            digitalWrite(13,HIGH);
            break;
          case 'w':
            digitalWrite(13,LOW);
            break; 
          case 'I':
            set_and_turn(-2);
            drive();
            break; 
          case 'G':
            set_and_turn(2);
            drive();
            break;
            
            
            
        }
      }
    else
    {
      time_notrecive = millis();
      if(time_notrecive - time_recive > TIMEOUT)
        stop();
    }
}
