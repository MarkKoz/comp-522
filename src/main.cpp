#include <Arduino.h>
#include <Stepper.h>

// Based on information from https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
const uint16_t STEPS_PER_REVOLUTION = 2038;

// Adjustable range is 0-15 RPM.
const uint8_t SPEEDS[4] = {2, 7, 11, 15};

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    static uint8_t speed_index = 0;
    static Stepper stepper(STEPS_PER_REVOLUTION, 8, 10, 9, 11);

    stepper.setSpeed(SPEEDS[speed_index]);
    stepper.step(1);
}
