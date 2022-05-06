#include <Arduino.h>

const uint_fast8_t ONE_VOLT = 51; // (51 / 255) * 5 = 1 volt

enum note : uint_fast8_t
{
    note_c = 0,
    note_db = 1,
    note_d = 2,
    note_eb = 3,
    note_e = 4,
    note_f = 5,
    note_gb = 6,
    note_g = 7,
    note_ab = 8,
    note_a = 9,
    note_bb = 10,
    note_b = 11
};

void set_note(enum note note, uint_fast8_t octave);
void set_voltage(float voltage);

void setup()
{
    for (uint8_t i = 0; i < 8; ++i) {
        pinMode(i, OUTPUT);
    }
}

void loop()
{
    for (uint_fast8_t octave = 0; octave < 5; ++octave) {
        for (uint_fast8_t i = 0; i < 12; ++i) {
            set_note(static_cast<note>(i), octave);
            delay(250); // 8th note at 120 bpm
        }
    }
}

void set_note(enum note note, uint_fast8_t octave)
{
    set_voltage(octave + (static_cast<uint_fast8_t>(note) / 12.0F));
}

void set_voltage(float voltage)
{
    PORTD = static_cast<uint8_t>(lroundf(ONE_VOLT * voltage));
}
