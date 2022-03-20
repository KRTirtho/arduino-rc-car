import 'package:controller/models/command.dart';
import 'package:flutter/material.dart';

final List<Command> group1Commands = [
  Command("Forward", "F"),
  Command("Backward", "B"),
  Command("Stop", "T"),
];

final List<Command> group2Commands = [
  Command("Left", "L"),
  Command("Right", "R"),
];

final List<Command> combinedCommands = [
  Command("ForwardLeft", "G"),
  Command("ForwardRight", "I"),
  Command("BackwardLeft", "J"),
  Command("BackwardRight", "H")
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
  Command? activeGroup1Command;

  Command? activeGroup2Command;

  @override
  Widget build(BuildContext context) {
    if (activeGroup1Command != null && activeGroup2Command == null) {
      widget.onCommand(activeGroup1Command!);
    } else if (activeGroup2Command != null && activeGroup1Command == null) {
      widget.onCommand(activeGroup2Command!);
    } else if (activeGroup1Command != null &&
        activeGroup1Command?.title != "Stop" &&
        activeGroup2Command != null) {
      widget.onCommand(
        combinedCommands.firstWhere((command) =>
            activeGroup1Command!.title + activeGroup2Command!.title ==
            command.title),
      );
    }
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [
        Row(
          children: group1Commands
              .map((command) => GestureDetector(
                    onTapUp: (e) {
                      setState(() {
                        activeGroup1Command = command;
                      });
                    },
                    onTapDown: (e) => setState(() {
                      activeGroup1Command = null;
                    }),
                    child: ElevatedButton(
                      child: Text(command.title),
                      onPressed: () {},
                    ),
                  ))
              .toList(),
        ),
        Row(
          children: group2Commands
              .map((command) => GestureDetector(
                    onTapUp: (e) {
                      setState(() {
                        activeGroup2Command = command;
                      });
                    },
                    onTapDown: (e) => setState(() {
                      activeGroup2Command = null;
                    }),
                    child: ElevatedButton(
                      child: Text(command.title),
                      onPressed: () {},
                    ),
                  ))
              .toList(),
        )
      ],
    );
  }
}
