# Robotics Projects — Marco Faria

General Engineering student at the University of Cambridge, building
mechatronics/embedded projects on the side — mostly Arduino-based
electromechanical systems, designed and 3D-printed (Bambu Lab A1) at home.

**Live site:** https://mf879.github.io/robotics-projects/

## Projects

| # | Project | Status | Summary |
|---|---------|--------|---------|
| 01 | [Light-Seeking Turret](01-light-seeking-turret/) | ✅ Working | Servo turret sweeps, detects the brightest light source via an LDR, locks on with a laser + buzzer confirmation |
| 02 | [Light-Following Car](02-light-following-car/) | 🚧 In progress | Two-wheel LDR-steered car; chassis printed, driver electronics bring-up paused pending soldering |
| 03 | Self-Balancing Robot | 🗓 Planned | Next build — IMU + PID balancing on the N20 gear motors with encoders |

## Why these projects

Each one bench-tests its subsystems individually before integration —
sensor read, actuator drive, and control logic are each proven in
isolation first (see each project's `bringup-tests/` folder), then
combined into the final closed-loop behaviour. That process is documented
per project below.

## Hardware on hand

Arduino Uno R3 · DRV8833 dual motor driver · N20 micro gear motors w/
encoders · servo motors · MPU-style IMU/gyroscope · buck converter · 6xAA
battery pack · Elegoo electronics fundamentals kit (LDRs, resistors,
transistors, 74HC595, breadboards, etc.) · laser diode module · Bambu Lab
A1 3D printer for custom mounts/chassis.

## About this repo

Code was prototyped with AI-assisted drafting, then reviewed, tested on
hardware, and adapted by hand — noted per project below rather than
presented as written from scratch, since that's the honest and, frankly,
more useful account of how it came together.
