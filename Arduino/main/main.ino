#include "AX12A.h"

#define DirectionPin    (10)
#define BaudRate        (57600)
#define MAX_POSITION    (30)
#define BASIC_SPEED     (200)
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



class Dynamixel : public AX12A
{
    private:
        int pos;

    public:
    Dynamixel()
    {
        begin(BaudRate, DirectionPin, &Serial2);
        setEndless(ID, OFF);
        pos = 0;
    }

    void setPos(int _pos = 0)
    {
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
        return readPosition(ID);
    }

    void turn()
    {
        int time = millis();
        while (pos != getPos())
        {
            moveSpeed(ID,pos,BASIC_SPEED);
            delay(100);
            if(millis() - time >= TIMEOUT) return;
        }
    }
    void set_and_turn(int _pos = 0)
    {
      setPos(_pos);
      turn();
    }

};


Dynamixel srv;

void setup() 
{
    Serial.begin(9600);
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


void loop()
{
    delay(600);
    drive(255);
    delay(600);
    drive(-255);
    delay(600);
    stop();
    delay(600);
    srv.set_and_turn(25);
    delay(600);
    drive(255);
    delay(600);
    srv.set_and_turn(0);
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
