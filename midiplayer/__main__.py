import argparse

from midiplayer import player


def main() -> None:
    """Parse CLI arguments."""
    parser = argparse.ArgumentParser(prog="midiplayer")
    subparsers = parser.add_subparsers(title="commands", dest="command")

    play_help = "play a MIDI file"
    play_parser = subparsers.add_parser("play", help=play_help, description=play_help)
    play_parser.add_argument(
        "file", type=argparse.FileType("rb"), help="path to the MIDI file to play"
    )
    play_parser.add_argument("port", help="name of the MIDI port to use")

    ports_help = "list MIDI output ports"
    subparsers.add_parser("ports", help=ports_help, description=ports_help)

    args = parser.parse_args()

    if args.command == "play":
        player.play(args.file, args.port)
    elif args.command == "ports":
        player.print_output_ports()
    else:
        parser.print_usage()


if __name__ == "__main__":
    main()
