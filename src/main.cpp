#include <Arduino.h>

const uint8_t BUTTON_PIN = 2;
const uint8_t LED_RED_PIN = 11;
const uint8_t LED_GREEN_PIN = 10;
const uint8_t LED_BLUE_PIN = 9;

const int16_t MIN_PERIOD = 1000; // 1 Hz
const int16_t MAX_PERIOD = MIN_PERIOD / 8; // 8 Hz
const uint8_t DEBOUNCE_THRESHOLD = 10; // 10 ms
const uint8_t RGB_PERIOD = 5; // 5 ms

void cycle_led_colours(uint8_t colour[]);
void set_led_colour(uint8_t red, uint8_t green, uint8_t blue);

void setup()
{
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
    static int button_state_prev = LOW;
    static bool led_blinking = false;
    static bool led_on = true;

    static unsigned long button_time_prev = 0;
    static unsigned long colour_time_prev = 0;
    static unsigned long time_prev = 0;

    static int16_t period = MIN_PERIOD;
    static uint8_t colour[3] = {255, 0, 0};

    const unsigned long time = millis();
    const int button_state = digitalRead(BUTTON_PIN);

    if (!led_blinking) {
        // When it's not blinking, cycle colours base on the RGB_PERIOD.
        if ((time - colour_time_prev) >= RGB_PERIOD) {
            cycle_led_colours(colour);
            colour_time_prev = time;
        }
    } else if ((time - time_prev) >= static_cast<uint16_t>(period)) {
        // When it is blinking, every period, alternate between on and off.
        // The colour should stay at the last colour shown before blinking was enabled.
        if (led_on) {
            set_led_colour(0, 0, 0);
        } else {
            set_led_colour(colour[0], colour[1], colour[2]);
        }
        time_prev = time;
        led_on = !led_on;
    }

    const bool button_pressed = button_state == HIGH && button_state != button_state_prev;
    if (button_pressed && (time - button_time_prev) >= DEBOUNCE_THRESHOLD) {
        if (!led_blinking) {
            led_blinking = true;
        } else {
            // If it's about to cycle to the min period, disable blinking.
            if (period == MAX_PERIOD) {
                led_blinking = false;
            }

            // Frequency needs to be signed because MIN_PERIOD > MAX_PERIOD.
            // Thus, subtracting MIN_PERIOD makes numbers go negative.
            period = ((period / 2 - MIN_PERIOD) % (MAX_PERIOD / 2 - MIN_PERIOD)) + MIN_PERIOD;
        }
        button_time_prev = time;
    }
    button_state_prev = button_state;
}

void cycle_led_colours(uint8_t colour[])
{
    static uint8_t colour_i = 0;
    static uint8_t colour_j = 1;
    static uint8_t colour_val = 0;

    if (colour_val == 255) {
        colour_i = (colour_i + 1) % 3;
        colour_j = (colour_j + 1) % 3;
        colour_val = 0;
    }

    colour[colour_i] -= 1;
    colour[colour_j] += 1;
    ++colour_val;

    set_led_colour(colour[0], colour[1], colour[2]);
}

void set_led_colour(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    analogWrite(LED_RED_PIN, red);
    analogWrite(LED_GREEN_PIN, green);
    analogWrite(LED_BLUE_PIN, blue);
}
