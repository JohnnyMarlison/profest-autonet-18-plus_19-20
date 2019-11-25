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

uint8_t     speed = 0,
        direction = 0;
bool    moving_forward = 1;

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
    Serial.readBytes(command, 2);
    speed           = command[0];
    moving_forward  = command[1] & 1;
    direction       = (command[1] >> 1) & 3;
    if(speed > 10){
    analogWrite(  PWM1,   speed);
    digitalWrite( INA1,   (speed > 0)?direction:!direction);
    digitalWrite( INB1,   (speed > 0)?!direction:direction);
    }
    else
    {
      digitalWrite( INA1, LOW);
      digitalWrite( INB1, LOW);
    }
    if(direction){
      analogWrite(  PWM1,   150);
      digitalWrite( INA2,   (direction == 1)?LOW:HIGH);
      digitalWrite( INB2,   (direction == 1)?HIGH:LOW);
    }
    else
    {
      digitalWrite( INA2, LOW);
      digitalWrite( INB2, LOW);
    }
}
