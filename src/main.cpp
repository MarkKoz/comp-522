#include <Arduino.h>
#include <Stepper.h>

const uint8_t SPEED_BUTTON = 2;
const uint8_t STOP_BUTTON = 4;

// Based on information from https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
const uint16_t STEPS_PER_REVOLUTION = 2038;

// Adjustable range is 0-15 RPM.
const uint8_t SPEEDS[4] = {2, 7, 11, 15};

void setup()
{
    Serial.begin(9600);
    pinMode(SPEED_BUTTON, INPUT_PULLUP);
    pinMode(STOP_BUTTON, INPUT_PULLUP);
}

void loop()
{
    static uint8_t speed_index = 0;
    static bool stopped = false;
    static Stepper stepper(STEPS_PER_REVOLUTION, 8, 10, 9, 11);

    if (digitalRead(STOP_BUTTON) == LOW) {
        stopped = !stopped;
    }

    if (!stopped) {
        stepper.setSpeed(SPEEDS[speed_index]);
        stepper.step(1);
    }
}
