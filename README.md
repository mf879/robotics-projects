# Embedded projects

Arduino and C++ builds I have designed, wired and tested myself. Each folder holds the code, the wiring, the bench tests and what I would change next.

Marco Faria, second year General Engineering, University of Cambridge.

Start with the self balancing robot if you only look at one.

---

## Projects

### [01 – Light seeking turret](01-light-seeking-turret)
Two axis turret that finds the brightest point in the room using four LDRs in a bridge arrangement and drives two servos to face it. Covers analogue reading, differential sensing and servo control.

### [02 – Light following robot](02-light-following-robot)
Two wheeled robot that steers toward a light source using paired LDRs and a motor driver. Differential drive, deadband handling and speed scaling with error.

### [03 – Temperature control system](03-temperature-control-system)
Thermostat built around an NTC thermistor and a relay driven heater. Beta equation conversion from resistance to temperature, hysteresis to stop the relay chattering, and a safe default state on startup.

### [04 – Self balancing robot](04-self-balancing-robot)
Inverted pendulum robot held upright by an MPU6050 and a PID loop driving two motors through a DRV8833. Sensor fusion, loop timing and gain tuning.

---

## What is in each folder

- **README.md** – what the build does, how it works, the circuit and the results
- **Source code** – the `.ino` sketches, commented
- **Media** – photos and video of the build running, where I have them
- **Notes** – wiring, parts used, known limitations and next steps

---

## Hardware and tools

- **Boards:** Arduino Uno and Nano
- **Sensors:** LDRs, NTC thermistors, MPU6050 IMU
- **Actuators:** DC motors, servos, relay modules
- **Drivers:** L298N, DRV8833
- **Languages:** C++ (Arduino), Python, MATLAB
- **Other:** SolidWorks, 3D printing, soldering and bench testing

---

## How I work

Every build here started as a breadboard circuit before anything was mounted. I test each subsystem on its own, check the sensor readings against something known, then close the loop. Where a build has a limitation I have written it down rather than left it out.

---

## Contact

- **Email:** mf879@cam.ac.uk
- **GitHub:** [github.com/mf879](https://github.com/mf879)

## About this repo

Code was prototyped with AI-assisted drafting, then reviewed, tested on
hardware, and adapted by hand — noted per project below rather than
presented as written from scratch, since that's the honest and, frankly,
more useful account of how it came together.
