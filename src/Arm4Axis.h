#ifndef ARM4AXIS_H
#define ARM4AXIS_H

#include <Arduino.h>
#include <Servo.h>
#include "math.h"

//griperBounds
#define gripMaxDist 57
#define gripMinDist 0
#define gripMaxAngle 75
#define gripMinAnge 160

#define ballSize 20 //change this
#define gripOpen 70 //change this too

#define SIDE_LENGTH 81


class Arm4Axis {
  private:

    Servo griperServo;
    Servo baseServo;
    Servo rightServo;
    Servo leftServo;

    int griperPin;
    int basePin;
    int rightPin;
    int leftPin;

    float RightServoOffset;
    float LeftServoOffset;

    // Inverse Kinematics
    float c_length;
    float k_angle;
    float cosine_iso;
    float a_angle;
    float b_angle;
    float c_angle;
    float k_b_angle;
    float x_angle;
    float w_angle;
    float servo4_atr;
    float servo3_atr;
    float y_angle;
    float cosine_debugging;
    float k_angle_degrees;
    float rad;
    float a_angle_convert;


    float degrees_1(float rad);

  public:

    Arm4Axis();
    Arm4Axis(int griperPin, int basePin, int rightPin, int leftPin);

    void setOffsets(int RightServoOffset, int LeftServoOffset); //fill in the parameters
    void setPins(int griperPin, int basePin, int rightPin, int leftPin);
    void initArm();

    void moveTheta(int angle);
    void moveGripper(int distToOpen);
    void moveRZ(int r, int z);
    void moveToAngle(int griper, int base, int right, int left);

    void grabBall();
    void relaseBall();
    void moveNeutral();
};

#endif
