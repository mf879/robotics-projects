/*
  Bring-up test: potentiometer read
  -----------------------------------
  Originally: manualandlaser.ino

  Purpose: confirm an analog input (a potentiometer on A1) reads cleanly,
  as a stepping stone toward manual/override servo positioning. Despite
  the original filename, this particular script only exercises the
  potentiometer read — it doesn't drive the laser.
*/

const int potPin = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);

  Serial.println(potValue);

  delay(100);
}
