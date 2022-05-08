#include <Arduino.h>
#include <ardumidi.h>

const uint_fast8_t ONE_VOLT = 51; // (51 / 255) * 5 = 1 volt
const uint_fast8_t NOTES_PER_OCTAVE = 12;
const uint_fast8_t MIDI_OCTAVE_OFFSET = 2; // Start at C1 instead of C-1.

const uint_fast8_t PIN_MUTE = 9;

const byte MIDI_ALL_SOUNDS_OFF = 120;
const byte MIDI_ALL_NOTES_OFF = 123;

inline bool is_reset_msg(const MidiMessage& msg) __attribute__((always_inline));
inline void set_note(uint_fast8_t note, uint_fast8_t octave) __attribute__((always_inline));
inline void set_voltage(float voltage) __attribute__((always_inline));

void setup()
{
    Serial.begin(115200);

    for (uint8_t i = 0; i < 8; ++i) {
        pinMode(i, OUTPUT);
    }

    pinMode(PIN_MUTE, OUTPUT);
    digitalWrite(PIN_MUTE, HIGH); // Start muted.
}

void loop()
{
    if (midi_message_available() > 0) {
        MidiMessage msg = read_midi_message();
        if (msg.channel != 0)
            return;

        if (msg.command == MIDI_NOTE_ON) {
            auto note = static_cast<uint_fast8_t>(msg.param1);

            // This may end up doing some redundant calculations,
            // but the code is easier to understand this way.
            set_note(note % NOTES_PER_OCTAVE, (note / NOTES_PER_OCTAVE) - MIDI_OCTAVE_OFFSET);
            digitalWrite(PIN_MUTE, LOW);
        } else if (msg.command == MIDI_NOTE_OFF || is_reset_msg(msg)) {
            digitalWrite(PIN_MUTE, HIGH);
        }
    }
}

bool is_reset_msg(const MidiMessage& msg)
{
    return msg.command == MIDI_CONTROLLER_CHANGE
        && (msg.param1 == MIDI_ALL_NOTES_OFF || msg.param1 == MIDI_ALL_SOUNDS_OFF);
}

void set_note(const uint_fast8_t note, const uint_fast8_t octave)
{
    set_voltage(octave + (note / 12.0F));
}

void set_voltage(const float voltage)
{
    PORTD = static_cast<uint8_t>(lroundf(ONE_VOLT * voltage));
}
