# Light-Seeking Turret

A servo-mounted turret that scans a room with an LDR (light-dependent
resistor), detects the brightest light source (e.g. a torch), and locks
onto it — switching on a laser pointer and sounding a buzzer as
confirmation.



![Demo](light-seeking-turret-demo.gif)



## How it works

1. **Calibrate** — on startup, average several LDR readings with no torch
   present to establish a "room light" baseline.
2. **Scan** — sweep the servo across its range in fixed steps, taking an
   averaged LDR reading at each angle.
3. **Detect** — compare each reading against the baseline (with a margin,
   to avoid false triggers from normal light fluctuation). On this LDR's
   wiring, a *brighter* source gives a *smaller* analog reading.
4. **Lock on** — stop at the angle where the target was found, turn on the
   laser, chirp the buzzer, and hold that position until the board is
   reset.

Full code: [`src/light_seeking_turret.ino`](src/light_seeking_turret.ino)

## Hardware

- Arduino Uno R3
- SG90-class servo (turret pan axis)
- LDR in a voltage-divider (signal into A0)
- Laser diode module
- Buzzer

## Build process

Each subsystem was bench-tested on its own before being combined into the
closed-loop sketch above — see [`bringup-tests/`](bringup-tests/):

- [`ldr_test.ino`](bringup-tests/ldr_test.ino) — confirms the LDR reads
  sensibly and established the "brighter = smaller value" behaviour the
  final logic depends on.
- [`servo_sweep_test.ino`](bringup-tests/servo_sweep_test.ino) — confirms
  wiring and a safe min/centre/max angle range before mounting.
- [`potentiometer_test.ino`](bringup-tests/potentiometer_test.ino) —
  analog-input bring-up, a stepping stone toward manual override control.

## Notes

- Code was first drafted with AI assistance, then tested on hardware and
  reviewed line-by-line to confirm the calibration/margin logic actually
  matches how this specific LDR and laser module behave.
- `lightMargin` is the main value to tune: too low and it triggers on
  ambient light drift; too high and it misses a dim torch.

