#include <Arduino.h>

const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 13;

const uint16_t MIN_FREQ = 1000; // 1 Hz
const uint16_t MAX_FREQ = MIN_FREQ / 8; // 8 Hz

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
    static int button_state_prev = LOW;
    static uint8_t led_state = LOW;
    static uint16_t frequency = MIN_FREQ;

    int button_state = digitalRead(BUTTON_PIN);
    if (button_state == HIGH && button_state != button_state_prev) {
        frequency = ((frequency / 2 - MIN_FREQ) % (MAX_FREQ / 2 - MIN_FREQ)) + MIN_FREQ;
    }
    button_state_prev = button_state;

    led_state = ~led_state;
    digitalWrite(LED_PIN, led_state);

    delay(frequency);
}
