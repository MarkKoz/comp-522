#include <Arduino.h>

const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 13;

const int16_t MIN_PERIOD = 1000; // 1 Hz
const int16_t MAX_PERIOD = MIN_PERIOD / 8; // 8 Hz

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
    static int button_state_prev = LOW;
    static uint8_t led_state = LOW;
    static int16_t period = MIN_PERIOD;

    int button_state = digitalRead(BUTTON_PIN);
    if (button_state == HIGH && button_state != button_state_prev) {
        // Frequency needs to be signed because MIN_PERIOD > MAX_PERIOD.
        // Thus, subtracting MIN_PERIOD makes numbers go negative.
        period = ((period / 2 - MIN_PERIOD) % (MAX_PERIOD / 2 - MIN_PERIOD)) + MIN_PERIOD;
    }
    button_state_prev = button_state;

    led_state = ~led_state;
    digitalWrite(LED_PIN, led_state);

    delay(static_cast<uint16_t>(period));
}
