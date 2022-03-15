#ifndef TANK_MOTORS_H
#define TANK_MOTORS_H

#include <Arduino.h>

#define ML_Ctrl 13  //define the direction control pin of left motor
#define ML_PWM 11   //define the PWM control pin of left motor
#define MR_Ctrl 12  //define the direction control pin of right motor
#define MR_PWM 3   //define the PWM control pin of righ

#define ML_Speed 200
#define MR_Speed 200

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
    byte _pinLeftDirection;
    byte _pinLeftPWM;
    byte _pinRightDirection;
    byte _pinRightPWM;
    int _driveSpeedLeft   = ML_Speed;
    int _driveSpeedRight  = MR_Speed;
};
#endif
