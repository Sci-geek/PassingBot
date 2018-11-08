#include "Arm4Axis.h"

using namespace std;




//<<constructor>>
Arm4Axis::Arm4Axis(){
  //defult constructor
}
Arm4Axis::Arm4Axis(int griperPin, int basePin, int rightPin, int leftPin){
  this->griperPin = griperPin;
  this->basePin = basePin;
  this->rightPin = rightPin;
  this->leftPin = leftPin;
  griperServo.attach(this->griperPin);
  baseServo.attach(this->basePin);
  rightServo.attach(this->rightPin);
  leftServo.attach(this->leftPin);
  moveNeutral();
  printf("init servo\n");

}

void Arm4Axis::setPins(int griperPin, int basePin, int rightPin, int leftPin){
  this->griperPin = griperPin;
  this->basePin = basePin;
  this->rightPin = rightPin;
  this->leftPin = leftPin;
}

void Arm4Axis::initArm(){
  griperServo.attach(this->griperPin);
  baseServo.attach(this->basePin);
  rightServo.attach(this->rightPin);
  leftServo.attach(this->leftPin);
}

void Arm4Axis::setOffsets(int RightServoOffset, int LeftServoOffset){
  this->RightServoOffset = RightServoOffset;
  this-> LeftServoOffset = LeftServoOffset;
}

void Arm4Axis::moveNeutral(){
  griperServo.write(90);
  baseServo.write(90);
  rightServo.write(90);
  leftServo.write(90);
}

void Arm4Axis::moveTheta(int angle) {
  baseServo.write(angle);
}

void Arm4Axis::moveGripper(int distToOpen) {
  if (distToOpen > gripMaxDist){
    griperServo.write(gripMaxAngle);
    return;
  }
  int val = map(distToOpen, gripMinDist, gripMaxDist, gripMinAnge, gripMaxAngle);     // scale it to use it with the servo (value between 0 and 180)
  griperServo.write(val);                  // sets the servo position according to the scaled value
}

void Arm4Axis::moveRZ(int r, int z){
  /*This method calculates the angle that the servos should move
  * based upon the Cartesian coordinates passed (r, z) = (x, y).
  *
  * Parameters: the float r is the location on the x axis that the
  * user wants the arm to move to, z is the location on the y axis
  * that the user wants the arm to move to
  */
  c_length = sqrt(r*r + z*z);
  k_angle_degrees = acos(r/c_length);
  // converts the radians returned to degrees
  k_angle = degrees_1(k_angle_degrees);
  cosine_iso = (c_length*c_length) / (2 * SIDE_LENGTH * c_length);
  a_angle = acos(cosine_iso);
  // converts the radians returned to degrees
  a_angle = degrees_1(a_angle);
  b_angle = a_angle;
  c_angle = 180 - (a_angle * 2);
  k_b_angle = k_angle + a_angle;
  x_angle = 90 - k_b_angle;
  y_angle = 90 - x_angle;
  w_angle = 180 - c_angle - y_angle;

  servo4_atr = LeftServoOffset - w_angle;
  servo3_atr = RightServoOffset - k_b_angle;

  leftServo.write(servo4_atr);    // short arm
  delay(300);
  rightServo.write(servo3_atr);    // long arm
  delay(300);

}
void Arm4Axis::moveToAngle(int griper, int base, int right, int left){
  griperServo.write(griper);
  baseServo.write(base);
  rightServo.write(right);
  leftServo.write(left);
}

float Arm4Axis::degrees_1(float rad) {
  // Helper function that converts radians to degrees
  return rad / 2 / M_PI * 360;
}
