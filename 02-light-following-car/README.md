# Light-Following Car

**Status: 🚧 paused mid-build** — chassis is 3D-printed and ready; wiring
paused because the second DRV8833 motor driver arrived without its pin
headers soldered on. Resuming once the soldering kit arrives.

## Goal

A two-wheeled car that steers toward the brightest light source, using
the same LDR-sensing approach proven in the [light-seeking turret](../01-light-seeking-turret/)
project, but driving two wheels differentially instead of panning a
single servo.

## Hardware

- Arduino Uno R3
- 2x DRV8833 dual motor drivers (one currently unsoldered — the blocker)
- 2x N20 micro gear motors w/ encoders (6V), with printed wheel hubs
- Chassis — designed and 3D-printed on a Bambu Lab A1
- LDR pair (left/right) for steering comparison
- Buck converter + 6xAA battery pack for motor power
- Breadboard wiring for now; may move to a soldered perfboard later

## Progress so far

- ✅ Chassis printed and fitted to the N20 gear motors
- ✅ One DRV8833 channel bench-tested — see
  [`src/drv8833_motor_test.ino`](src/drv8833_motor_test.ino), confirming
  forward/stop/reverse control at a safe reduced PWM for the 6V motors
- ⏸ Second driver's headers need soldering before both motor channels
  (and therefore steering) can be wired up
- ⏳ Not yet started: dual-LDR steering logic (compare left vs. right
  light level, drive differentially toward the brighter side)

## Plan once unblocked

1. Solder headers onto the second DRV8833
2. Wire both motor channels + both LDRs
3. Bring up both motors together (extend the single-channel test)
4. Write the differential-steering control loop (left/right LDR
   comparison → motor speed bias), following the same calibrate-then-scan
   pattern used in the turret project
5. Test, tune, and add before/after demo video
