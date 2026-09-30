# Self-Balancing Robot

A two-wheeled robot that balances itself using an MPU6050 IMU and a PID control loop, built on a custom 3D-printed chassis.

---

https://github.com/user-attachments/assets/791188ea-c791-42bf-b146-ca7c9511a6f7



## Overview

- Arduino Uno reads tilt from an MPU6050 (accelerometer + gyro, combined with a complementary filter)
- A PID loop converts that tilt into motor commands via a TB6612FNG driver
- Two N20 motors correct the lean in real time, keeping the robot upright

---

## Hardware

| Component | Notes |
|---|---|
| Arduino Uno | Main controller |
| MPU6050 (GY-521) | IMU - accelerometer + gyro over I2C |
| TB6612FNG | Dual motor driver |
| 2x N20 motors + wheels | Drive motors |
| 6xAA battery pack (~9V) | Motor + logic power |
| Buck converter | Regulates battery voltage down to 5V logic rail |
| Custom 3D-printed chassis | Single-piece tapered spine (see below) |

---

## Chassis Design

The chassis is a single printed spine rather than a hollow tiered box:

- Narrow (20mm) where it's just structural spine
- Widens locally only where a component needs support: battery pocket at the top, Arduino platform in the middle, driver + MPU6050 near the bottom
- No cantilevered shelves - every wide section is directly under what it supports, avoiding flex that would read as false tilt on the IMU
- Battery placed high (heaviest single part) to give better inverted-pendulum dynamics
- MPU6050 mounted as close to axle height as possible, for the cleanest tilt signal

---

## Wiring

**Power**
- Battery (+) -> buck converter IN+, and directly to TB6612FNG VM
- Battery (-) -> buck converter IN-, shared ground rail
- Buck converter OUT (5V) -> Arduino 5V, TB6612FNG VCC + STBY, MPU6050 VCC

**Motors**
- Left motor -> AO1 / AO2
- Right motor -> BO1 / BO2

**Driver control**
| Signal | Arduino pin |
|---|---|
| AIN1 | D8 |
| AIN2 | D7 |
| PWMA | D9 |
| BIN1 | D2 |
| BIN2 | D4 |
| PWMB | D5 |

**MPU6050**
| Pin | Connects to |
|---|---|
| VCC | 5V rail |
| GND | Ground rail |
| SCL | A5 |
| SDA | A4 |

---

## How It Works

**Tilt angle (complementary filter)**

Combines the accelerometer's stable-but-noisy angle with the gyro's smooth-but-drifting rate:

angle = a . (angle + gyroRate . dt) + (1 - a) . accAngle

where a is close to 1 (e.g. 0.90), so the gyro dominates moment-to-moment and the accelerometer quietly corrects long-term drift.

**PID control**

error = target - angle
output = Kp.error + Ki.integral(error) + Kd.derivative(error)

- Kp - proportional response to how far off balance it is
- Ki - corrects small persistent lean (imperfect centre of mass)
- Kd - damps oscillation; computed from the gyro rate directly rather than differencing noisy angle readings

**Motor output**

`output` maps to PWM + direction on both motors, with:
- a small deadzone so tiny PID outputs don't get force-amplified into a kick
- a minimum PWM floor to overcome gearbox stiction
- integral clamping to prevent windup
- a slow drift-compensation term that nudges the target angle to counter sustained one-directional creep

---

## Debugging Journey

A few real bugs worth noting, since they weren't obvious at first:

- **Sensor axis mismatch** - the tilt formula was written assuming the X-axis responded to tilt. Once mounted in the chassis, it was actually the Z-axis. Found by logging raw ax/ay/az while tilting and watching which one actually moved.
- **Derivative noise** - computing `derivative` from `(error - lastError) / dt` amplified sensor noise badly at fast loop speeds. Fixed by using the gyro rate directly instead.
- **Integral windup** - unclamped integral term caused erratic, oversized corrections. Fixed by clamping it.
- **Deadband overcorrection** - forcing every nonzero output up to a minimum PWM caused small necessary corrections to overshoot. Fixed with a small deadzone before applying the minimum.


