#include <tank_motors.h>

#define LINE_SENSOR_PIN_1 2
#define LINE_SENSOR_PIN_2 6
#define LINE_SENSOR_PIN_3 7
#define LINE_SENSOR_PIN_4 8
#define LINE_SENSOR_PIN_5 10


#define LINE_COLOR          0
#define BACKGROUND_COLOR    1
#define SENSOR_COUNT        5
Tank_Motors  motors;              // motor controls

bool state[SENSOR_COUNT];
int  activeSensors = 0; 
// -2 (full left) through +2 (full right), representing overall sensor sum
int  sum = 0; 
unsigned long confusionStart = 0;

void setup() {
  Serial.begin(9600);

  motors.setDriveSpeed(130,130);

  pinMode(LINE_SENSOR_PIN_1, INPUT);
  pinMode(LINE_SENSOR_PIN_2, INPUT);
  pinMode(LINE_SENSOR_PIN_3, INPUT);
  pinMode(LINE_SENSOR_PIN_4, INPUT);
  pinMode(LINE_SENSOR_PIN_5, INPUT);
  
}

void loop() {
  readLineSensor();
  action();
  debug();
}

void action() {
  switch (activeSensors) {
    case 0:
    case SENSOR_COUNT:
      // all are reading the same.
//      motors.stop(); // we have no idea what's going on
      if ((millis() - confusionStart) < 1000) {
        Serial.println("Confusion Mode");
        wiggle();
      } else {
        motors.stop();
      }
      break;
    default:
      switch(sum) {
        case -2:
          motors.spinLeft();
          break;
        case -1:
          motors.curveLeft();
          break;
        case 0: 
          motors.forward();
          break;
        case 1:
          motors.curveRight();
          break;
        case 2:
          motors.spinRight();
          break;
      }
      confusionStart = millis();
      Serial.println("Reset confusion start to " + String(confusionStart) + " based on " + String(millis()));
      Serial.println("Therefore Confused: " + String(millis() - confusionStart));
 
  }
    
}

void readLineSensor() {
  state[0] = digitalRead(LINE_SENSOR_PIN_1);
  state[1] = digitalRead(LINE_SENSOR_PIN_2);
  state[2] = digitalRead(LINE_SENSOR_PIN_3);
  state[3] = digitalRead(LINE_SENSOR_PIN_4);
  state[4] = digitalRead(LINE_SENSOR_PIN_5);

  activeSensors = 0;
  sum = 0; 
  for(int i = 0 ; i < SENSOR_COUNT; i++) {

    if (state[i] == LINE_COLOR) {
      activeSensors ++;
      sum = sum + (i - (SENSOR_COUNT/2));
    }
  }
}

void wiggle() {
  if (random(1, 100) % 2 == 0) {
    motors.spinLeft();
  } else {
    motors.spinRight();
  }
  delay(100);
  motors.back();
  delay(100);
  motors.stop();
}

void debug() {
  Serial.print(digitalRead(LINE_SENSOR_PIN_1));
  Serial.print(digitalRead(LINE_SENSOR_PIN_2));
  Serial.print(digitalRead(LINE_SENSOR_PIN_3));
  Serial.print(digitalRead(LINE_SENSOR_PIN_4));
  Serial.println(digitalRead(LINE_SENSOR_PIN_5));
  Serial.print("ActiveSensors count: " + String(activeSensors));
  Serial.println(", Sum: " + String(sum));
  Serial.println("Confused for: " + String(millis() - confusionStart));
  Serial.println("");
}
