#ifndef TANK_MOTORS_H
#define TANK_MOTORS_H

#include <Arduino.h>

#define ML_Ctrl 13  // Direction control pin of left motor
#define ML_PWM 11   // PWM control pin of left motor
#define MR_Ctrl 12  // Direction control pin of right motor
#define MR_PWM 3    // PWM control pin of right motor

#define ML_Speed 200  //default left  motor drive speed
#define MR_Speed 200  //default right motor drive speed

class Tank_Motors {
  public:
    Tank_Motors(
      byte pinLeftDirection = ML_Ctrl, 
      byte pinLeftPWM = ML_PWM, 
      byte pinRightDirection = MR_Ctrl, 
      byte pinRightPWM = MR_PWM
    );
    void setDriveSpeed(int leftSpeed, int rightSpeed);
    void forward();
    void back();
    void stop();
    void curveLeft(float slowSpeedAdjustment = 0.5);
    void curveRight(float slowSpeedAdjustment = 0.5);
    void spinLeft();
    void spinRight();
  private:
    void drive(int leftDirection, int leftSpeed, int rightDirection, int rightSpeed);
    byte _pinLeftDirection;
    byte _pinLeftPWM;
    byte _pinRightDirection;
    byte _pinRightPWM;
    int _driveSpeedLeft   = ML_Speed;
    int _driveSpeedRight  = MR_Speed;
};
#endif
