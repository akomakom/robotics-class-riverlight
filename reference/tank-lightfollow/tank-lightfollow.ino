#include <tank_matrix.h>
#include <tank_motors.h>

#define light_L_Pin A1   //define the pin of left photo resistor
#define light_R_Pin A2   //define the pin of right photo resistor

#define LIGHT_THRESHOLD 300 // consider this reading a bright light
#define DIFFERENCE_RANGE 300 // This much difference in light intensity (or more) means do a hard spin

Tank_Matrix matrix(A4, A5, A3);   // display board
Tank_Motors  motors;              // motor control library

void setup() {
  Serial.begin(9600);
  pinMode(light_L_Pin, INPUT);
  pinMode(light_R_Pin, INPUT);

  Serial.println("lightfollow init");
  matrix.display(String(matrix.getVoltage(), 1));
  delay(1000);
  matrix.display("");
}

void loop() {
  int left_light = analogRead(light_L_Pin);
  int right_light = analogRead(light_R_Pin);

  // provide visual indication of intensities
  // Let's assume that 200-1000 is the useful range
  matrix.drawMeter(left_light, 200, 1000, 60, 3);
  matrix.drawMeter(right_light, 200, 1000, 15, 3);
  matrix.drawVoltageMeter();
  
  // debugging don't print too often
//  if (millis() % 100 == 0) {
//    Serial.print("voltage = ");
//    Serial.print(matrix.getVoltage());
//    Serial.print(", left_light_value = ");
//    Serial.print(left_light);
//    Serial.print(", right_light_value = ");
//    Serial.println(right_light);
//  }

  if (left_light > LIGHT_THRESHOLD || right_light > LIGHT_THRESHOLD) {
    // at least one side is getting enough light, so let's drive
    int difference = left_light - right_light;
    if (difference > 0) {
      // Left is brigher than right
      // slow the non-turning side down proportionally
//      Serial.print("Left difference factor: "); Serial.println(1.0 - 1.0*difference/DIFFERENCE_RANGE);
      motors.curveLeft(1.0 - 1.0*difference/DIFFERENCE_RANGE); 
    } else {
      // Right is brigher than left
      // slow the non-turning side down proportionally
//      Serial.print("Right difference factor: "); Serial.println(1.0 + 1.0*difference/DIFFERENCE_RANGE);
      motors.curveRight(1.0 + 1.0*difference/DIFFERENCE_RANGE); 
    }
  } else {
    motors.stop();
  }

// A less math-heavy approach:
  
//  if ((left_light - right_light) > DIFFERENCE_RANGE) {
//    // One is significantly brigher than the other
//    motors.spinLeft();
//  } else if ((right_light - left_light) > DIFFERENCE_RANGE) {
//    // One is significantly brigher than the other
//    motors.spinRight();
//  } else if ((left_light - right_light) > DIFFERENCE_RANGE_CURVE) {
//    // One is significantly brigher than the other
//    motors.curveLeft();
//  } else if ((right_light - left_light) > DIFFERENCE_RANGE_CURVE) {
//    // One is significantly brigher than the other
//    motors.curveRight();
//  } else if (left_light > LIGHT_THRESHOLD && right_light > LIGHT_THRESHOLD) {
//    // Both sides are pretty bright and similar.  Let's go forward.
//    motors.forward();
//  } else {
//    //other situations, stop
//    motors.stop();
//  }
}

//****************************************************************
