#include "tank_motors.h"

/*
   Simplified motor control library specific to the tank
*/

Tank_Motors::Tank_Motors( 
      byte pinLeftDirection, 
      byte pinLeftPWM, 
      byte pinRightDirection, 
      byte pinRightPWM) {

  pinMode(pinLeftDirection, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightDirection, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);  

  _pinLeftDirection = pinLeftDirection;
  _pinLeftPWM = pinLeftPWM;
  _pinRightDirection = pinRightDirection;
  _pinRightPWM = pinRightPWM;
}

/**
 * Allows us to change individual speeds for left/right motor
 * in case the tank doesn't drive straight.  Default is ML_Speed/MR_Speed
 */
void Tank_Motors::setDriveSpeed(int leftSpeed, int rightSpeed) {
  _driveSpeedLeft   = leftSpeed;
  _driveSpeedRight  = rightSpeed;
}

void Tank_Motors::forward() {
  drive(LOW, _driveSpeedRight, LOW, _driveSpeedLeft);
}
void Tank_Motors::back() {
  drive(HIGH, _driveSpeedRight, HIGH, _driveSpeedLeft);
}
void Tank_Motors::stop() {
  drive(LOW, 0, LOW, 0);
}
void Tank_Motors::curveLeft(int slowSpeedAdjustmentPercent) {
  //prevent bad values > 100 or < 0
  drive(LOW, _driveSpeedRight, LOW,  _driveSpeedLeft * max(0, min(100, slowSpeedAdjustmentPercent)) / 100);
}
void Tank_Motors::curveRight(int slowSpeedAdjustmentPercent) {
  //prevent bad values > 100 or < 0
  drive(LOW, _driveSpeedRight * max(0, min(100, slowSpeedAdjustmentPercent)) / 100, LOW, _driveSpeedLeft);
}
void Tank_Motors::spinLeft() {
  drive(LOW, _driveSpeedRight, HIGH, _driveSpeedLeft);
}
void Tank_Motors::spinRight() {
  drive(HIGH, _driveSpeedRight, LOW, _driveSpeedLeft);
}

void Tank_Motors::drive(int rightDirection, int rightSpeed, int leftDirection, int leftSpeed) {
  digitalWrite(_pinRightDirection, rightDirection);
  analogWrite(_pinRightPWM, rightSpeed);
  digitalWrite(_pinLeftDirection, leftDirection);
  analogWrite(_pinLeftPWM, leftSpeed);
}
