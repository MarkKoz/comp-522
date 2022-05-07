#include <Arduino.h>
#include <ardumidi.h>

const uint_fast8_t ONE_VOLT = 51; // (51 / 255) * 5 = 1 volt
const uint_fast8_t NOTES_PER_OCTAVE = 12;
const uint_fast8_t MIDI_OCTAVE_OFFSET = 2; // Start at C1 instead of C-1.

void set_note(uint_fast8_t note, uint_fast8_t octave);
void set_voltage(float voltage);

void setup()
{
    Serial.begin(115200);

    for (uint8_t i = 0; i < 8; ++i) {
        pinMode(i, OUTPUT);
    }
}

void loop()
{
    if (midi_message_available() > 0) {
        MidiMessage msg = read_midi_message();
        if (msg.command == MIDI_NOTE_ON && msg.channel == 0) {
            auto note = static_cast<uint_fast8_t>(msg.param1);

            // This may end up doing some redundant calculations,
            // but the code is easier to understand this way.
            set_note(note % NOTES_PER_OCTAVE, (note / NOTES_PER_OCTAVE) - MIDI_OCTAVE_OFFSET);
        }
    }
}

void set_note(uint_fast8_t note, uint_fast8_t octave)
{
    set_voltage(octave + (note / 12.0F));
}

void set_voltage(float voltage)
{
    PORTD = static_cast<uint8_t>(lroundf(ONE_VOLT * voltage));
}
