#include <Arduino.h>

const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 13;

const int16_t MIN_PERIOD = 1000; // 1 Hz
const int16_t MAX_PERIOD = MIN_PERIOD / 8; // 8 Hz
const uint8_t DEBOUNCE_THRESHOLD = 10; // 10 ms

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
    static int button_state_prev = LOW;
    static uint8_t led_state = LOW;

    static unsigned long button_time_prev = 0;
    static unsigned long time_prev = 0;
    static int16_t period = MIN_PERIOD;

    unsigned long time = millis();
    if ((time - time_prev) >= static_cast<uint16_t>(period)) {
        time_prev = time;
        led_state = ~led_state;
        digitalWrite(LED_PIN, led_state);
    }

    int button_state = digitalRead(BUTTON_PIN);
    if (button_state == HIGH && button_state != button_state_prev) {
        if ((time - button_time_prev) >= DEBOUNCE_THRESHOLD) {
            button_time_prev = time;
            // Frequency needs to be signed because MIN_PERIOD > MAX_PERIOD.
            // Thus, subtracting MIN_PERIOD makes numbers go negative.
            period = ((period / 2 - MIN_PERIOD) % (MAX_PERIOD / 2 - MIN_PERIOD)) + MIN_PERIOD;
        }
    }
    button_state_prev = button_state;
}
