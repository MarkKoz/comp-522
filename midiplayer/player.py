import io

import mido


def play(file: io.RawIOBase, output_port_name: str) -> None:
    """Play a MIDI file in the given port."""
    midi_file = mido.MidiFile(file=file)

    with mido.open_output(output_port_name, autoreset=True) as port:
        try:
            for msg in midi_file.play():
                port.send(msg)
        except BaseException as e:
            port.panic()
            if not isinstance(e, KeyboardInterrupt):
                raise


def print_output_ports() -> None:
    """Print the names of MIDI output ports."""
    print("\n".join(mido.get_output_names()))
