#define PIN_MOTOR_LEFT_DIRECTION 13  //define the direction control pin of left motor
#define PIN_MOTOR_LEFT_SPEED 11   //define the PWM control pin of left motor
#define PIN_MOTOR_RIGHT_DIRECTION 12  //define the direction control pin of right motor
#define PIN_MOTOR_RIGHT_SPEED 3   //define the PWM control pin of right motor

void setup() {
  pinMode(PIN_MOTOR_LEFT_DIRECTION, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_SPEED, OUTPUT);
}

void loop() {
  // LOW is forward.  HIGH is backward.
  digitalWrite(PIN_MOTOR_LEFT_DIRECTION, LOW);
  analogWrite(PIN_MOTOR_LEFT_SPEED, 120);
}
