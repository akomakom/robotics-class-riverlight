#define light_L_Pin A1   //define the pin of left photo resistor
#define light_R_Pin A2   //define the pin of right photo resistor
#define ML_Ctrl     13  //define the direction control pin of left motor
#define ML_PWM      11   //define the PWM control pin of left motor
#define MR_Ctrl     12  //define the direction control pin of right motor
#define MR_PWM      3   //define the PWM control pin of right motor

int left_light;
int right_light;

// This runs once on startup
void setup() {
  Serial.begin(9600);
  pinMode(light_L_Pin, INPUT);
  pinMode(light_R_Pin, INPUT);
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
}

// This runs over and over
void loop() {
  left_light = analogRead(light_L_Pin);
  right_light = analogRead(light_R_Pin);
  
  Serial.print("left_light_value = ");
  Serial.println(left_light);
  Serial.print("right_light_value = ");
  Serial.println(right_light);

  // TODO: What should we do with this now?
}

/******************************************************
* Car control methods below:
******************************************************/
void Car_front()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 200);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 200);
}
void Car_left()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 200);
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 200);
}
void Car_right()
{
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 200);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 200);
}
void Car_Stop()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 0);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 0);
}
//****************************************************************
