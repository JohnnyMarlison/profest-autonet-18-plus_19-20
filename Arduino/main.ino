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

char command[2];

void loop()
{
  if (Serial.available()) {
    Serial.readBytes(command, 2);
    _speed           = int(command[0]);
    moving_forward  = int(command[1] & 1);
    turnside       = int((command[1] >> 1));
    Serial.print(_speed);
    Serial.print(" ");
    Serial.print(moving_forward);
    Serial.print(" ");
    Serial.print(turnside);
    Serial.println();
  }
  if (_speed > 0) {
    digitalWrite( INA1,   !moving_forward);
    digitalWrite( INB1,   moving_forward);
    analogWrite(PWM1, _speed);
  }
  else
  {
    digitalWrite( INA1, LOW);
    digitalWrite( INB1, LOW);
  }
  if (turnside != 0) {
    digitalWrite( INA2,   (turnside == 1) ? LOW : HIGH);
    digitalWrite( INB2,   (turnside == 1) ? HIGH : LOW);
    digitalWrite( PWM2,   HIGH);
  }
  else
  {
    digitalWrite( INA2, LOW);
    digitalWrite( INB2, LOW);
  }
}

