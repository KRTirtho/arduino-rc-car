import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class DeviceTile extends StatelessWidget {
  final Function()? onTap;
  final BluetoothDevice device;

  DeviceTile({this.onTap, required this.device});

  @override
  Widget build(BuildContext context) {
    return ListTile(
      onTap: onTap,
      leading: Icon(Icons.devices),
      title: Text(device.name ?? "Unknown device"),
      subtitle: Text(device.address.toString()),
      trailing: ElevatedButton(
        child: Text('Connect'),
        onPressed: onTap,
      ),
    );
  }
}
