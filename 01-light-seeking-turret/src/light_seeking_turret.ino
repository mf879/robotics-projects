
#include <Servo.h>

Servo turret;

// ---- Pin assignments ----
const int servoPin  = 9;
const int laserPin   = 4;
const int buzzerPin  = 3;
const int ldrPin     = A0;

// ---- Sweep range ----
const int minAngle    = 10;
const int centreAngle = 90;
const int maxAngle    = 170;
const int stepSize    = 4;   // degrees per sweep step — smaller = finer scan, slower sweep

// ---- LDR wiring polarity ----
// If your laser output logic is inverted on your specific module, swap these.
const int LASER_ON  = HIGH;
const int LASER_OFF = LOW;

// From bench testing: with this LDR's voltage-divider orientation, a
// BRIGHTER light source produces a SMALLER analogRead() value.
const bool brighterIsSmaller = true;

// How far below (or above) the calibrated room-light baseline a reading
// must be before it counts as "target found". Increase if it locks onto
// ambient light too easily; decrease if it fails to detect the torch.
const int lightMargin = 120;

int roomLightLevel = 0;

void setup() {
  Serial.begin(9600);

  turret.attach(servoPin);
  pinMode(laserPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(laserPin, LASER_OFF);

  // Park at centre before calibrating so the calibration reading isn't
  // taken while the servo is mid-sweep.
  turret.write(centreAngle);
  delay(1000);

  Serial.println("Calibrating room light...");
  Serial.println("Keep torch OFF during calibration.");
  roomLightLevel = readLightAverage();
  Serial.print("Room light level = ");
  Serial.println(roomLightLevel);

  Serial.println("Scanning until target found...");
}

void loop() {
  // Sweep low -> high, then high -> low, repeating until lockOn() traps
  // the program in its own infinite loop.
  for (int angle = minAngle; angle <= maxAngle; angle += stepSize) {
    scanAngle(angle);
  }
  for (int angle = maxAngle; angle >= minAngle; angle -= stepSize) {
    scanAngle(angle);
  }
}

// Move to one angle, take a light reading there, and check whether it's
// bright enough to count as a detected target.
void scanAngle(int angle) {
  turret.write(angle);
  delay(50); // let the servo settle before sampling light

  int lightValue = readLightAverage();

  Serial.print("angle=");
  Serial.print(angle);
  Serial.print(" light=");
  Serial.println(lightValue);

  if (targetFound(lightValue)) {
    lockOn(angle, lightValue);
  }
}

// Compare a light reading against the calibrated baseline (with margin).
bool targetFound(int lightValue) {
  if (brighterIsSmaller) {
    return lightValue < roomLightLevel - lightMargin;
  } else {
    return lightValue > roomLightLevel + lightMargin;
  }
}

// Freeze the turret on the detected angle, confirm with laser + a rising
// three-tone chirp, then hold that position forever (reset the board to
// scan again).
void lockOn(int angle, int lightValue) {
  turret.write(angle);
  delay(300);
  digitalWrite(laserPin, LASER_ON);

  Serial.println("TARGET FOUND");
  Serial.print("LOCKED angle=");
  Serial.print(angle);
  Serial.print(" light=");
  Serial.println(lightValue);

  tone(buzzerPin, 1000, 120);
  delay(180);
  tone(buzzerPin, 1400, 120);
  delay(180);
  tone(buzzerPin, 1800, 250);
  delay(300);
  noTone(buzzerPin);

  // Stay locked forever. Press the Arduino RESET button to scan again.
  while (true) {
    turret.write(angle);
    digitalWrite(laserPin, LASER_ON);
    delay(100);
  }
}

// Average several LDR samples to smooth out sensor/electrical noise
// before comparing against the baseline.
int readLightAverage() {
  long total = 0;
  for (int i = 0; i < 8; i++) {
    total += analogRead(ldrPin);
    delay(3);
  }
  return total / 8;
}
