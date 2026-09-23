# Light-Following Robot

A two-wheeled robot that steers towards a light source by comparing two LDRs.

<!-- Put a photo or a short clip here. Ten seconds of it following a torch is the single
     best thing you can add to this repo. -->

## What it does

An LDR sits on each side of the front of the robot. At startup the robot samples both
sensors 50 times and stores the average as its ambient baseline. In the main loop it
reads both again and works out how far above that baseline each one is.

- If neither side is more than 20 counts above baseline, there is no target and the
  robot stops.
- If one side is more than 40 counts brighter than the other, that wheel is slowed to
  60 while the other stays at 150, so the robot curves towards the light.
- If both sides are similar, both wheels run at 150 and it drives straight.

## How it works

- **Sensing:** two LDRs in voltage dividers on A0 (right) and A1 (left).
- **Calibration:** `calibrateBaseline()` averages 50 samples at startup, so the robot
  works in a bright room as well as a dark one without changing the code.
- **Steering:** differential drive. The turn is made by slowing one wheel rather than
  reversing it, which gives a smooth curve instead of a pivot.
- **Drive:** DRV8833 dual motor driver. Channel A is the right motor (AIN1 = 2,
  AIN2 = 4, PWMA = 5), channel B is the left (BIN1 = 7, BIN2 = 8, PWMB = 9).
- **Chassis:** designed in SolidWorks and 3D-printed on a Bambu Lab A1, including the
  wheel hubs that fit the N20 output shafts.

## Why the PWM is capped

The motors are rated 6 V and the pack is 8.4 V. Running full PWM would put the whole
8.4 V across them. A duty of 150 out of 255 keeps the average voltage inside the motor
rating, so the drive speed in the code is a limit, not an arbitrary number.

## Hardware

- Arduino Uno
- 2 x LDR in voltage dividers
- DRV8833 dual motor driver
- 2 x N20 micro gear motors
- 8.4 V battery pack
- 3D-printed chassis and wheel hubs

## Files

- `final_light_robot.ino` — the finished robot
- `Ldrtest.ino` — prints both LDR readings, used to check the sensors and pick thresholds
- `motortesting.ino` — drives both motors forward and back, used to confirm wiring and direction
- `turntesting.ino` — adds pivot turns, used to check which way each wheel drives

Each subsystem was tested on its own before anything was combined.

## Known limitations

- The baseline is taken once at startup. If a bright light is already pointed at it
  while it calibrates, that light becomes "normal" and the robot will not react to it.
- It slows a wheel rather than reversing one, so there is a minimum turn radius. It
  cannot spin on the spot to find a light behind it.
- With no target it stops rather than searching.

## What I learned

- Calibrating at startup mattered more than picking a good fixed threshold. Without it
  the robot behaved completely differently from one room to the next.
- Testing the sensors and each motor channel separately first meant that when the
  assembled robot misbehaved, I already knew the low-level parts were fine.
