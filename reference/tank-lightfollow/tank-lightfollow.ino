/*
  keyestudio Mini Tank Robot v2.0
  lesson 10
  Light-following tank
  http://www.keyestudio.com
*/
#define light_L_Pin A1   //define the pin of left photo resistor
#define light_R_Pin A2   //define the pin of right photo resistor
#define ML_Ctrl 13  //define the direction control pin of left motor
#define ML_PWM 11   //define the PWM control pin of left motor
#define MR_Ctrl 12  //define the direction control pin of right motor
#define MR_PWM 3   //define the PWM control pin of right motor

#define LIGHT_THRESHOLD 600 // consider this reading a bright light
#define DIFFERENCE_THRESHOLD 200 // significant left vs right difference

int left_light;
int right_light;

void setup() {
  Serial.begin(9600);
  pinMode(light_L_Pin, INPUT);
  pinMode(light_R_Pin, INPUT);
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
}

void loop() {
  left_light = analogRead(light_L_Pin);
  right_light = analogRead(light_R_Pin);

  // don't print too often
  if (millis() % 100) {
    Serial.print("left_light_value = ");
    Serial.print(left_light);
    Serial.print(", right_light_value = ");
    Serial.println(right_light);
  }

  if (abs(left_light - right_light) > DIFFERENCE_THRESHOLD) {
    //ignore absolute values, just trust the difference
    if (right_light > left_light) {
      Car_right();
    } else {
      Car_left();
    }
  } else if (left_light > LIGHT_THRESHOLD && right_light > LIGHT_THRESHOLD) //the value detected photo resistor，go front
  {
    Car_front();
  }
  else  //other situations, stop
  {
    Car_Stop();
  }
}

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
