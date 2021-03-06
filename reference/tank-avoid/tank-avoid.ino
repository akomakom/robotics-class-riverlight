#include <tank_matrix.h>
#include <tank_motors.h>

// driving constants
#define TURN_TIME 500 // time it takes to make an obstacle-avoiding turn
#define DISTANCE_OBSTRUCTION 50

// ultrasonic sensor  constants
#define ANGLE_STRAIGHT 88 // 90 if the servo is perfectly mounted
#define ANGLE_LEFT     170 // these left/right values seem to get us about 180 degrees
#define ANGLE_RIGHT    1

#define RANGEFINDER_TRIGGER 5  //ultrasonic RANGEFINDER_TRIGGER Pin
#define RANGEFINDER_ECHO    4  //ultrasonic RANGEFINDER_ECHO Pin
#define servoPin 9  //servo Pin

Tank_Matrix matrix(A4, A5, A3);   // display board
Tank_Motors  motors;              // motor controls


//The function to control servo
void set_servo_angle(int myangle) {
  for (int i = 0; i <= 50; i = i + 1) {
    int pulsewidth = myangle * 11 + 500;
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servoPin, LOW);
    delay((20 - pulsewidth / 1000));
  }
}
//The function to control ultrasonic sensor
float checkdistance() {
  digitalWrite(RANGEFINDER_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(RANGEFINDER_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(RANGEFINDER_TRIGGER, LOW);
  float distance = pulseIn(RANGEFINDER_ECHO, HIGH) / 58.00;  //58.20, that is, 2*29.1=58.2
  return distance;
}

/**
 * Repeat distance measurement several times, average the result
 */
float checkdistance_average() {
  int result = 0;
  // the data will be more accurate if ultrasonic sensor detect a few times.
  for (int j = 0; j < 10; j++) {
    result += checkdistance();
    delay(10);
  }
  return result / 10;
}

//****************************************************************
void setup() {
  pinMode(servoPin, OUTPUT);
  set_servo_angle(ANGLE_STRAIGHT); //set servo to 90°

  pinMode(RANGEFINDER_TRIGGER, OUTPUT);
  pinMode(RANGEFINDER_ECHO, INPUT);

}
void loop() {
  int random2 = random(1, 100);
  int forward_distance = checkdistance();  //assign the front distance detected by ultrasonic sensor to variable a

  if (forward_distance < 40) //when the front distance detected is less than 20
  {
    motors.stop();  //robot stops
    delay(300); //delay to allow vehicle to stop

    set_servo_angle(ANGLE_LEFT);  //Ultrasonic platform turns left
//    delay(100);
    int left_distance = checkdistance_average();  //assign the left distance detected by ultrasonic sensor to variable left_distance
//    matrix.display(String(left_distance).substring(0, 3));
    matrix.drawMeter(left_distance, 0, 100, 90);
    Serial.println(left_distance);
//    delay(300);
    set_servo_angle(ANGLE_RIGHT); //Ultrasonic platform turns right
//    delay(100);
    int right_distance = checkdistance_average(); //assign the right distance detected by ultrasonic sensor to variable right_distance
//    matrix.display(String(right_distance).substring(0, 3));
    matrix.drawMeter(right_distance, 0, 100, 15);
    Serial.println(right_distance);
//    delay(300);
    set_servo_angle(ANGLE_STRAIGHT);  //Ultrasonic platform turns back to right ahead

    //robot will turn to the longer distance side when left or right distance is less than 50cm.
    if (left_distance < DISTANCE_OBSTRUCTION || right_distance < DISTANCE_OBSTRUCTION)  
    {
      if (left_distance > right_distance) //left distance is greater than right side
      {
        matrix.display(">");
        motors.spinLeft();  //robot turns left
      }
      else
      {
        matrix.display("<");
        motors.spinRight(); //robot turns right
      }
    }
    else  //If both side is greater than or equal to 50cm, turn left or right randomly
    {
      matrix.display("?"); // random direction, both sides seem open
      if ((long) (random2) % (long) (2) == 0)  //When the random number is even
      {
        motors.spinLeft(); //tank robot turns left
      }
      else
      {
        motors.spinRight(); //robot turns right
      }
    }

    delay(TURN_TIME);  // Let motors run this long to turn
    motors.forward(); //go front

  }
  else  //If the front distance is greater than or equal to 20cm, robot car will go front
  {
    motors.forward(); //go front
  }
}
