/*
  Bring-up test: DRV8833 motor driver
  -------------------------------------
  Originally: motortest.ino

  Purpose: confirm one motor channel of the DRV8833 dual driver is wired
  correctly and can run an N20 gear motor forward, stop, and reverse, at a
  reduced PWM duty cycle (these are 6V-rated N20 motors, so testPWM is
  kept well below the full 255 range while confirming direction control).

  Status: this is as far as the light-following car got before the build
  paused — the second DRV8833 needed pin headers soldered on before both
  motor channels (and therefore steering) could be wired up. Chassis is
  already 3D-printed and waiting. See ../README.md for full status.
*/

const int IN1 = 5;
const int IN2 = 6;

const int testPWM = 80;   // start low for 6V N20 motor
const int maxPWM   = 130; // do not go above this for now

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  // forward at reduced voltage
  runMotor(testPWM);
  delay(1000);

  // stop
  runMotor(0);
  delay(1000);

  // backward at reduced voltage
  runMotor(-testPWM);
  delay(1000);

  // stop
  runMotor(0);
  delay(1000);
}

void runMotor(int speedValue) {
  speedValue = constrain(speedValue, -maxPWM, maxPWM);

  if (speedValue > 0) {
    analogWrite(IN1, speedValue);
    analogWrite(IN2, 0);
  }
  else if (speedValue < 0) {
    analogWrite(IN1, 0);
    analogWrite(IN2, -speedValue);
  }
  else {
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
  }
}
