# COMP 565 - Project 3: Final Project

Course Title: Embedded Applications<br/>
Semester: Spring 2022<br/>

## Program Description

Send a control voltage which will be the input to a VCO. Each octave is 1 volt and has 12 notes. Each note is 1/12th of a volt. Since the Arduino operates on 5 volts, there can at most be 5 octaves.

### MIDI

The program receives MIDI commands over the serial port. The [Hairless MIDI to Serial Bridge](https://projectgus.github.io/hairless-midiserial/) can be used to connect a MIDI input port to the Arduino's serial port. Furthermore, on Windows, [loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html) can be used to create a virtual MIDI input port. Programs can send command to this virtual port, and Hairless will forward the messages to the Arduino.

Only the following MIDI commands are supported, and they are only respected for channel 0. All other commands and channels are ignored.

* Note on/off
    * Only for notes C1 to C6, inclusive
    * Velocity is ignored
* Controller change
    * Only for `ALL_SOUNDS_OFF` and `ALL_NOTES_OFF`

#### Player

The `midiplayer` Python package can be used to play a MIDI file to a MIDI port (such as the virtual port created by loopMIDI). To install it, clone this repository and run `pip install .` in the root of the repository. For usage details, run `midiplayer -h` after installation.

## Circuitry

Pins 0 to 7 form an 8-bit integer which represents the control voltage, where 0 is 0 volts (C1) and 255 is 5 volts (C6). This has to be put through a DAC before it can be used with the VCO. Pin 9 is set high when sound should be muted by the VCO, and low otherwise.
