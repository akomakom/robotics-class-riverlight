/*
 keyestudio Mini Tank Robot v2.0
 lesson 11
 ultrasonic_avoid_tank
 http://www.keyestudio.com
*/
int random2;
int forward_distance;
int left_distance;
int right_distance;



#define ML_Ctrl 13  //define the direction control pin of left motor
#define ML_PWM 11   //define PWM control pin of left motor
#define MR_Ctrl 12  //define the direction control pin of right motor
#define MR_PWM 3    //define PWM control pin of right motor

// driving constants
#define TURN_TIME 500 // time it takes to make a turn

// ultrasonic server constants
#define ANGLE_STRAIGHT 90
#define ANGLE_LEFT     160
#define ANGLE_RIGHT    20

#define Trig 5  //ultrasonic trig Pin
#define Echo 4  //ultrasonic echo Pin
int distance;
#define servoPin 9  //servo Pin
int pulsewidth;

/************the function to run motor**************/
void Car_forward()
{
  digitalWrite(MR_Ctrl,LOW);
  analogWrite(MR_PWM,200);
  digitalWrite(ML_Ctrl,LOW);
  analogWrite(ML_PWM,245);
  display("FW");
}
void Car_back()
{
  digitalWrite(MR_Ctrl,HIGH);
  analogWrite(MR_PWM,200);
  digitalWrite(ML_Ctrl,HIGH);
  analogWrite(ML_PWM,200);
  display("RV");
}
void Car_left()
{
  digitalWrite(MR_Ctrl,LOW);
  analogWrite(MR_PWM,255);
  digitalWrite(ML_Ctrl,HIGH);
  analogWrite(ML_PWM,255);
  display(">");
}
void Car_right()
{
  digitalWrite(MR_Ctrl,HIGH);
  analogWrite(MR_PWM,255);
  digitalWrite(ML_Ctrl,LOW);
  analogWrite(ML_PWM,255);
  display("<");
}
void Car_Stop()
{
  digitalWrite(MR_Ctrl,LOW);
  analogWrite(MR_PWM,0);
  digitalWrite(ML_Ctrl,LOW);
  analogWrite(ML_PWM,0);
  display("X");
}

//The function to control servo
void set_server_angle(int myangle) {
  for (int i = 0; i <= 50; i = i + (1)) {
    pulsewidth = myangle * 11 + 500;
    digitalWrite(servoPin,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servoPin,LOW);
    delay((20 - pulsewidth / 1000));
  }
}
//The function to control ultrasonic sensor
float checkdistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  float distance = pulseIn(Echo, HIGH) / 58.00;  //58.20, that is, 2*29.1=58.2
  delay(10);
  return distance;
}
  //****************************************************************
void setup(){
  pinMode(servoPin, OUTPUT);
  set_server_angle(ANGLE_STRAIGHT); //set servo to 90°
  
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);

  matrix_setup();
}
void loop(){
  random2 = random(1, 100);
  forward_distance = checkdistance();  //assign the front distance detected by ultrasonic sensor to variable a
  
  if (forward_distance < 40) //when the front distance detected is less than 20 
  {
      Car_Stop();  //robot stops
      delay(300); //delay in 500ms
      set_server_angle(ANGLE_LEFT);  //Ultrasonic platform turns left
      for (int j = 1; j <= 10; j = j + (1)) { //for statement, the data will be more accurate if ultrasonic sensor detect a few times.
        left_distance = checkdistance();  //assign the left distance detected by ultrasonic sensor to variable left_distance
      }
      display(String(left_distance));
      Serial.println(left_distance);
      delay(500);
      set_server_angle(ANGLE_RIGHT); //Ultrasonic platform turns right
      for (int k = 1; k <= 10; k = k + (1)) {
        right_distance = checkdistance(); //assign the right distance detected by ultrasonic sensor to variable right_distance
      }
      display(String(right_distance)); 
      Serial.println(right_distance); 
      
      if (left_distance < 50 || right_distance < 50)  //robot will turn to the longer distance side when left or right distance is less than 50cm. 
      {
        if (left_distance > right_distance) //left distance is greater than right side      
        {
          set_server_angle(ANGLE_STRAIGHT);  //Ultrasonic platform turns back to right ahead         
Car_left();  //robot turns left
          delay(TURN_TIME);  //turn left for 500ms
          Car_forward(); //go front
        } 
        else 
        {
          set_server_angle(ANGLE_STRAIGHT);
          Car_right(); //robot turns right
          delay(TURN_TIME);
          Car_forward();  //go front
        }
      } 
      else  //If both side is greater than or equal to 50cm, turn left or right randomly
      {
        display("?"); // random direction
        if ((long) (random2) % (long) (2) == 0)  //When the random number is even
        {
          set_server_angle(ANGLE_STRAIGHT);
          Car_left(); //tank robot turns left
          delay(TURN_TIME);
          Car_forward(); //go front
        } 
        else 
        {
          set_server_angle(ANGLE_STRAIGHT);
          Car_right(); //robot turns right
          delay(TURN_TIME);
          Car_forward(); //go front
       }
     }
  } 
  else  //If the front distance is greater than or equal to 20cm, robot car will go front
  {
      Car_forward(); //go front
  }
}
