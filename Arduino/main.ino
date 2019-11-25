#define INA1 2
#define INB1 3
#define PWM1 4
#define INA2 5
#define INB2 6
#define PWM2 7
/*
*   2 - turn
*   1 - speed
*/

int     speed = 0,
        turnspeed = 0;
bool    angle = 0,
        direction = true;

void setup()
{
    pinMode(INA2, OUTPUT);
    pinMode(INA2, OUTPUT);
    pinMode(INB2, OUTPUT);
    pinMode(INB2, OUTPUT);
    pinMode(PWM1, OUTPUT);
    pinMode(PWM2, OUTPUT);
    Serial.begin(115200);
}

char *command;

void loop()
{
    command = "";
    while(!Serial.available());
    Serial.readBytes(command, 3);
    speed =     command[0];
    turnspeed = command[1];
    direction = command[2] & 1;
    angle =     command[2] & 2;
    analogWrite(  PWM1,   speed);
    digitalWrite( INA1,   (speed > 10)?direction:!direction);
    digitalWrite( INB1,   (speed > 10)?!direction:direction);
    analogWrite(  PWM1,   turnspeed);
    digitalWrite( INA2,   (turnspeed > 20)?angle:!angle);
    digitalWrite( INB2,   (turnspeed > 20)?!angle:angle);
}
