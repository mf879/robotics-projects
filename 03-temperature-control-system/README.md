# Arduino Thermostat

A closed-loop temperature controller that holds a set temperature by switching a heater
through a relay.

<!-- No video of this one. Add a photo of the hardware if it is still built, a wiring
     diagram, and a screenshot of the serial output crossing the setpoint. -->

## What it does

A 10k NTC thermistor is read on A0 and converted to degrees C using the Beta equation.
The heater is switched on when the temperature falls to 29 C and off when it reaches
31 C, holding roughly 30 C.

The 1 C band either side of the target is deliberate. Without it the relay would click
on and off continuously every time the reading crossed the setpoint.

## How it works

- **Sensing:** 10k NTC thermistor with a 10k series resistor. Resistance is calculated
  from the ADC reading, then converted with the Beta equation (Beta = 3950, nominal
  10k at 25 C).
- **Control:** on/off control with 1 C of hysteresis around a 30 C target.
- **Switching:** the heater is not driven from the Arduino. It runs from its own supply
  and is switched by an active-low relay module, with the Arduino only driving the
  relay input pin.
- **Fail-safe:** if the ADC reads at either rail, or the calculated temperature is
  outside -20 to 100 C, the sensor is treated as faulty and the heater is switched off.

## The problem I had to solve

The heater I started with drew more current than the 5 V supply could safely provide.
Rather than run it anyway or change the heating element, I moved the heater onto its own
higher voltage supply and switched it with a relay. The Arduino kept full control of
when it came on, but the current no longer went near the board.


## Hardware

- Arduino Uno
- 10k NTC thermistor, Beta 3950, with a 10k series resistor
- Active-low relay module on D8
- Heater running from a separate supply

## Files

- `final_thermostat.ino` — the finished controller
- `tempsensortest.ino` — prints the raw ADC reading, used to check the sensor was wired correctly
- `tempconversion.ino` — prints the converted temperature, used to check the Beta equation before adding control
- `relay_test.ino` — clicks the relay once, used to confirm the module was active low

## Safety note

The heater runs from its own supply and is isolated from the Arduino by the relay. Do
not power a heating element directly from a microcontroller board.

## What I learned

- A current limit is a design constraint, not something to work around. The fix was to
  change the power path, not the element.
- Hysteresis is what stops an on/off controller chattering at the setpoint.
- Converting and printing the temperature before writing any control logic made the
  control part straightforward, because I already trusted the reading.
