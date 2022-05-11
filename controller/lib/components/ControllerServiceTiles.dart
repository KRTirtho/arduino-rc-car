import 'package:controller/models/command.dart';
import 'package:flutter/material.dart';

const List<Command> commands = [
  Command("Forward", "F"),
  Command("Backward", "B"),
  Command("Right", "R"),
  Command("Left", "L"),
  Command("Safe Left", ">"),
  Command("Safe Right", "<"),
  Command("Stop", "T"),
  Command("Horn", "H"),
  Command("Front LED", "X"),
  Command("Back LED", "C"),
];

class ControllerServiceTiles extends StatefulWidget {
  final Function(Command) onCommand;
  const ControllerServiceTiles({
    required this.onCommand,
    Key? key,
  }) : super(key: key);

  @override
  State<ControllerServiceTiles> createState() => _ControllerServiceTilesState();
}

class _ControllerServiceTilesState extends State<ControllerServiceTiles> {
  @override
  Widget build(BuildContext context) {
    return Wrap(
      spacing: 10,
      runAlignment: WrapAlignment.center,
      alignment: WrapAlignment.center,
      crossAxisAlignment: WrapCrossAlignment.center,
      children: commands
          .map((command) => ElevatedButton(
                child: Text(command.title),
                onPressed: () {
                  widget.onCommand(command);
                },
              ))
          .toList(),
    );
  }
}
