# COMP 565 - Project 2: Motor

Course Title: Embedded Applications<br/>
Semester: Spring 2022<br/>

## Program Description

Build a state-machine embedded application as an Arduino sketch (program) that does the following...

* If the motor is stopped, when the user pushes a push-button (which I will call `INPUT1`), the motor begins rotating.
* If there is a `currVelocity` set, the motor rotates at this velocity.
* If `currVelocity` has not been set, the motor rotates at an initial slow velocity (chosen by you).
* If the motor is running, when the user pushes the push-button `INPUT1`, the motor speeds up again (to 2nd velocity, and beyond). Once the motor reaches the maximum velocity, additional pushes of `INPUT1` have no effect. The various velocities are chosen by you, but you must use at least 4 different velocities.
* If the motor is running, and the user activates another piece of input hardware (**YOUR CHOICE**... but I will call it `INPUT2`) the motor stops, but remembers its current velocity in variable `currVelocity`.
* If the motor is stopped, and the user activates `INPUT2`, the `currVelocity` is cleared (reset to 0).

**NOTE:** Much of this description has been left intentionally vague to allow for...

* different types of motor hardware to be used
* independent research into stepper motors

If you desire a "standard" Arduino reference for the Stepper motor and the Arduino Stepper API (Stepper.h), please consult the code/descriptions at https://www.arduino.cc/en/tutorial/stepperSpeedControl and https://www.arduino.cc/en/Reference/StepperStep

## Requirements

* The states are listed in an enumeration in the code, and have capital letters as their name.
* When a state is entered (including the initial state, named something like `INIT`), a function is called which is named after that state, like `stateInit(...)`.
* Each state function (named after the state, e.g. `stateInit(...)`) has two segments of code.
* A portion of code that is only executed once each time the state is entered.
* A portion of code that executes repeatedly as long as you're in the state (typically a conditional to see if we must transition out of the state).
* The `loop()` function has a switch statement inside which identifies the current state (e.g. `INIT`) and calls that state's function (e.g. `stateInit(...)`).
