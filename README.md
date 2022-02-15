# COMP 565 - Project 0: Warmup

Course Title: Embedded Applications<br/>
Semester: Spring 2022<br/>

## Program Description

When the board is powered on, its programmable LED blinks once per second (1 Hz). As the button is pressed, the board cycles through the following blink frequencies:

* 2 Hz
* 4 Hz
* 8 Hz
* 1 Hz

... and so on, for each new button press.

### Implementation

For the push-button to work, a pull-down resistor must be connected in series with it. Pull-down resistors will be discussed soon in lecture, but for now a tutorial on hooking up the push-button can be found [here](https://docs.arduino.cc/built-in-examples/digital/Button).
