# COMP 565 - Project 1: PWM Output, Analog Input

Course Title: Embedded Applications<br/>
Semester: Spring 2022<br/>

## Program Description

Design a dimmer for a light using a potentiometer (plugged into the breadboard) and an external LED (plugged into the breadboard, not the LED on the Arduino UNO board). You may use any potentiometer you wish to use on your board, however the 10k ohm potentiometer on Adafruit for $1.25 is recommended, or any potentiometer that may have come with your kit.

The LED should be connected to a PWM-enabled digital pin (any with a ~ next to it) and the potentiometer should be connected to an analog pin. You are responsible for mapping the analog input signal (which ranges from 0 to 1023) to the PWM output signal (which ranges from 0 to 255). Note that you will be using analogWrite(...) to control the PWM output even though it is on a digital pin.

Create a program (an Arduino sketch) that controls the brightness of the external LED via the potentiometer.
