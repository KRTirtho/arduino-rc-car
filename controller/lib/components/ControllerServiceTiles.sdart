import 'package:controller/models/command.dart';

import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';

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
  final BluetoothService service;
  const ControllerServiceTiles({
    required this.service,
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
    final write = widget.service.characteristics.first.write;
    if (activeGroup1Command != null && activeGroup2Command == null) {
      write(activeGroup1Command!.command);
    } else if (activeGroup2Command != null && activeGroup1Command == null) {
      write(activeGroup2Command!.command);
    } else if (activeGroup1Command != null &&
        activeGroup1Command?.title != "Stop" &&
        activeGroup2Command != null) {
      write(
        combinedCommands
            .firstWhere((command) =>
                activeGroup1Command!.title + activeGroup2Command!.title ==
                command.title)
            .command,
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
