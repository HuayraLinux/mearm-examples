/*
 * MeArm Arduino code to coonnect with MeArm Desktop appplication
 * developted on Huayra GNU/Linux.
 * 
 * Created 26/11/2015 by Matias De lellis <mati86dl@gmail.com>
 *  
 * This example code is in the public domain.
 */

#include <Servo.h>

const int basePin = 12;
const int shoulderPin = 11;
const int elbowPin = 9;
const int gripperPin = 10;

Servo base, shoulder, elbow, gripper;
int baseAngle = 90, shoulderAngle = 90, elbowAngle = 90, gripperAngle = 90;
int baseTAngle, shoulderTAngle, elbowTAngle, gripperTAngle;

unsigned long sequenceTime = 0;

void setup ()
{
  Serial.begin(9600);

  base.attach(basePin);
  shoulder.attach(shoulderPin);
  elbow.attach(elbowPin);
  gripper.attach(gripperPin);

  base.write (90);
  shoulder.write (90);
  elbow.write (90);
  gripper.write (90);
}

void loop ()
{
  int steps = 90;

  if (Serial.available() > 0)
  {
    baseTAngle = Serial.parseInt();
    shoulderTAngle = Serial.parseInt();
    elbowTAngle = Serial.parseInt();
    gripperTAngle = Serial.parseInt();

    for (int i = 0; i < steps; i++)
    {
      base.write (baseAngle + (baseTAngle - baseAngle)*i/steps);
      shoulder.write (shoulderAngle + (shoulderTAngle - shoulderAngle)*i/steps);
      elbow.write (elbowTAngle + (elbowTAngle - elbowAngle)*i/steps);
      gripper.write (gripperTAngle + (gripperTAngle - gripperAngle)*i/steps);

      while ((millis() - sequenceTime) < 5);
      sequenceTime = millis();
    }

    baseAngle = baseTAngle;
    shoulderAngle = shoulderTAngle;
    elbowAngle = elbowTAngle;
    gripperAngle = gripperTAngle;

    Serial.print("1");
  }  
}
