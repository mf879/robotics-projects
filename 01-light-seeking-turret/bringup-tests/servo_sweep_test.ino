/*
  Bring-up test: servo sweep
  ---------------------------
  Originally: turrettesting.ino

  Purpose: confirm the servo is wired correctly and check the safe angle
  range (minAngle/centreAngle/maxAngle) before mounting it on the turret
  body — a fixed sweep sequence with no sensor input yet.

  Once this range was confirmed safe, the same min/centre/max/step values
  were carried over into light_seeking_turret.ino.
*/

#include <Servo.h>

Servo turret;

const int servoPin = 9;

const int minAngle    = 5;
const int centreAngle = 90;
const int maxAngle    = 175;

void setup() {
  turret.attach(servoPin);
  turret.write(centreAngle);
  delay(1000);
}

void loop() {
  turret.write(minAngle);
  delay(1000);

  turret.write(centreAngle);
  delay(1000);

  turret.write(maxAngle);
  delay(1000);

  turret.write(centreAngle);
  delay(1000);
}
