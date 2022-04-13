#include <Arduino.h>
#include <Stepper.h>

const uint8_t SPEED_BUTTON = 2;
const uint8_t TOGGLE_BUTTON = 4;

const uint8_t DEBOUNCE_THRESHOLD = 20; // ms

// Based on information from https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
const uint16_t STEPS_PER_REVOLUTION = 2038;

// Adjustable range is 0-15 RPM.
const uint8_t SPEEDS[4] = {2, 7, 11, 15};

bool is_pressed(uint8_t pin, int& prev_state, unsigned long& prev_time);

void setup()
{
    Serial.begin(9600);
    pinMode(SPEED_BUTTON, INPUT_PULLUP);
    pinMode(TOGGLE_BUTTON, INPUT_PULLUP);
}

void loop()
{
    static uint8_t speed_index = 0;
    static bool stopped = false;

    static int speed_state = HIGH;
    static int toggle_state = HIGH;
    static unsigned long speed_time = 0;
    static unsigned long toggle_time = 0;

    static Stepper stepper(STEPS_PER_REVOLUTION, 8, 10, 9, 11);

    if (is_pressed(TOGGLE_BUTTON, toggle_state, toggle_time)) {
        stopped = !stopped;

        Serial.println("Toggled");
    }

    if (is_pressed(SPEED_BUTTON, speed_state, speed_time)) {
        speed_index = stopped ? 0 : (speed_index + 1) % 4;

        Serial.print("Speed is now ");
        Serial.println(speed_index);
    }

    if (!stopped) {
        stepper.setSpeed(SPEEDS[speed_index]);
        stepper.step(1);
    }
}

bool is_pressed(uint8_t pin, int& prev_state, unsigned long& prev_time)
{
    const int new_state = digitalRead(pin);
    const unsigned long time = millis();

    if (new_state == LOW && prev_state != LOW && (time - prev_time) >= DEBOUNCE_THRESHOLD) {
        prev_time = time;
        prev_state = new_state;
        return true;
    }

    prev_state = new_state;
    return false;
}
