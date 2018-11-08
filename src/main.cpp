#include <Arduino.h>
#include "Arm4Axis.h"

#define LeftGrip    8     // gripper,
#define LeftBase    11    // base
#define LeftRight   10    // right servo, long  arm
#define LeftLeft    9     // left servo, short arm


#define RightGrip   4     // gripper,
#define RightBase   7   // base
#define RightRight  5   // right servo, long  arm
#define RightLeft   6 // left servo, short arm

float LEFT_LEFT_OFFSET = 82;
float LEFT_RIGHT_OFFSET = 190;

float RIGHT_LEFT_OFFSET = 85;
float RIGHT_RIGHT_OFFSET = 175;

Arm4Axis *LeftArm = NULL;

Arm4Axis *RightArm = NULL;



void setup() {
  // put your setup code here, to run once:
  LeftArm = new Arm4Axis(LeftGrip, LeftBase, LeftRight, LeftLeft);
  LeftArm->setOffsets(LEFT_RIGHT_OFFSET, LEFT_LEFT_OFFSET);

  RightArm = new Arm4Axis(RightGrip, RightBase, RightRight, RightLeft);
  RightArm->setOffsets(RIGHT_RIGHT_OFFSET, RIGHT_LEFT_OFFSET);

}

void loop() {
  // put your main code here, to run repeatedly:
}
