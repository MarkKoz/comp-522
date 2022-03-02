#include <Arduino.h>

const uint8_t LED_PIN = 3;
const uint8_t POT_PIN = A5;
const float POT_TO_LED_FACTOR = 255.0F / 1023.0F;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(POT_PIN, INPUT);
}

void loop()
{
    int pot_value = analogRead(POT_PIN); // 10 bits; 0 to 1023
    int led_value = static_cast<int>(pot_value * POT_TO_LED_FACTOR); // 0 to 255
    analogWrite(LED_PIN, led_value);
}
