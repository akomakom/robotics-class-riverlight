#include <tank_matrix.h>
#include <tank_motors.h>

int random2;
int forward_distance;
int left_distance;
int right_distance;


// driving constants
#define TURN_TIME 500 // time it takes to make an obstacle-avoiding turn
#define DISTANCE_OBSTRUCTION 50

// ultrasonic server constants
#define ANGLE_STRAIGHT 90
#define ANGLE_LEFT     160
#define ANGLE_RIGHT    20

#define Trig 5  //ultrasonic trig Pin
#define Echo 4  //ultrasonic echo Pin
int distance;
#define servoPin 9  //servo Pin
int pulsewidth;

Tank_Matrix matrix(A4, A5, A3);   // display board
Tank_Motors  motors;              // motor control library



//The function to control servo
void set_servo_angle(int myangle) {
  for (int i = 0; i <= 50; i = i + (1)) {
    pulsewidth = myangle * 11 + 500;
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servoPin, LOW);
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

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

}
void loop() {
  random2 = random(1, 100);
  forward_distance = checkdistance();  //assign the front distance detected by ultrasonic sensor to variable a

  if (forward_distance < 40) //when the front distance detected is less than 20
  {
    motors.stop();  //robot stops
    delay(300); //delay in 500ms

    set_servo_angle(ANGLE_LEFT);  //Ultrasonic platform turns left
    left_distance = checkdistance_average();  //assign the left distance detected by ultrasonic sensor to variable left_distance
    matrix.display(String(left_distance).substring(0, 3));
    Serial.println(left_distance);
    delay(300);
    set_servo_angle(ANGLE_RIGHT); //Ultrasonic platform turns right
    right_distance = checkdistance_average(); //assign the right distance detected by ultrasonic sensor to variable right_distance
    matrix.display(String(right_distance).substring(0, 3));
    Serial.println(right_distance);
    delay(300);
    set_servo_angle(ANGLE_STRAIGHT);  //Ultrasonic platform turns back to right ahead

    if (left_distance < 50 || right_distance < 50)  //robot will turn to the longer distance side when left or right distance is less than 50cm.
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
