/*
  Bring-up test: LDR light sensor
  --------------------------------
  Originally: lightsensortest.ino

  Purpose: confirm the LDR voltage divider is wired correctly and that
  analogRead() returns sensible, changing values as light level changes,
  before writing any control logic that depends on it. Watch the Serial
  Monitor while covering/uncovering the sensor or pointing a torch at it —
  the values should move clearly and consistently.

  This baseline reading behaviour (brighter = smaller number, on this
  wiring) is what the final light_seeking_turret.ino relies on.
*/

const int ldrPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(ldrPin);

  Serial.println(lightValue);

  delay(100);
}
