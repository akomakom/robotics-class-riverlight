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
  _driveSpeedLeft = leftSpeed;
  _driveSpeedRight = rightSpeed;
}

void Tank_Motors::forward() {
  digitalWrite(_pinRightDirection, LOW);
  analogWrite(_pinRightPWM, _driveSpeedRight);
  digitalWrite(_pinLeftDirection, LOW);
  analogWrite(_pinLeftPWM, _driveSpeedLeft);
}
void Tank_Motors::back() {
  digitalWrite(_pinRightDirection, HIGH);
  analogWrite(_pinRightPWM, _driveSpeedRight);
  digitalWrite(_pinLeftDirection, HIGH);
  analogWrite(_pinLeftPWM, _driveSpeedLeft);
}
void Tank_Motors::stop() {
  digitalWrite(_pinRightDirection, LOW);
  analogWrite(_pinRightPWM, 0);
  digitalWrite(_pinLeftDirection, LOW);
  analogWrite(_pinLeftPWM, 0);
}
void Tank_Motors::curveLeft(float slowSpeedAdjustment = 0.5) {
  digitalWrite(_pinRightDirection, LOW);
  analogWrite(_pinRightPWM, _driveSpeedRight);
  digitalWrite(_pinLeftDirection, LOW);
  //prevent bad values > 1
  analogWrite(_pinLeftPWM, _driveSpeedLeft * max(0.0, min(1.0, slowSpeedAdjustment)));
}
void Tank_Motors::curveRight(float slowSpeedAdjustment = 0.5) {
  digitalWrite(_pinRightDirection, LOW);
  //prevent bad values > 1
  analogWrite(_pinRightPWM, _driveSpeedRight * max(0.0, min(1.0, slowSpeedAdjustment)));
  digitalWrite(_pinLeftDirection, LOW);
  analogWrite(_pinLeftPWM, _driveSpeedLeft);
}
void Tank_Motors::spinLeft() {
  digitalWrite(_pinRightDirection, LOW);
  analogWrite(_pinRightPWM, _driveSpeedRight);
  digitalWrite(_pinLeftDirection, HIGH);
  analogWrite(_pinLeftPWM, _driveSpeedLeft);
}
void Tank_Motors::spinRight() {
  digitalWrite(_pinRightDirection, HIGH);
  analogWrite(_pinRightPWM, _driveSpeedRight);
  digitalWrite(_pinLeftDirection, LOW);
  analogWrite(_pinLeftPWM, _driveSpeedLeft);
}
