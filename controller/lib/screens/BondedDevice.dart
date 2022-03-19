import 'dart:async';
import 'package:controller/components/DeviceTile.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class SelectBondedDevicePage extends StatefulWidget {
  /// If true, on page start there is performed discovery upon the bonded devices.
  /// Then, if they are not avaliable, they would be disabled from the selection.
  final bool checkAvailability;
  final Function(BluetoothDevice)? onChatPage;

  const SelectBondedDevicePage(
      {this.checkAvailability = true, @required this.onChatPage});

  @override
  _SelectBondedDevicePage createState() => new _SelectBondedDevicePage();
}

enum _DeviceAvailability {
  no,
  maybe,
  yes,
}

class _DeviceWithAvailability extends BluetoothDevice {
  BluetoothDevice device;
  _DeviceAvailability availability;
  int? rssi;

  _DeviceWithAvailability(this.device, this.availability, [this.rssi])
      : super(
            address: device.address,
            bondState: device.bondState,
            isConnected: device.isConnected,
            name: device.name,
            type: device.type);
}

class _SelectBondedDevicePage extends State<SelectBondedDevicePage> {
  List<_DeviceWithAvailability> devices = [];

  // Availability
  late StreamSubscription<BluetoothDiscoveryResult>
      _discoveryStreamSubscription;
  late bool _isDiscovering;

  _SelectBondedDevicePage();

  @override
  void initState() {
    super.initState();

    _isDiscovering = widget.checkAvailability;

    if (_isDiscovering) {
      _startDiscovery();
    }

    // Setup a list of the bonded devices
    FlutterBluetoothSerial.instance
        .getBondedDevices()
        .then((List<BluetoothDevice> bondedDevices) {
      setState(() {
        devices = bondedDevices
            .map(
              (device) => _DeviceWithAvailability(
                device,
                widget.checkAvailability
                    ? _DeviceAvailability.maybe
                    : _DeviceAvailability.yes,
              ),
            )
            .toList();
      });
    });
  }

  void _restartDiscovery() {
    setState(() {
      _isDiscovering = true;
    });

    _startDiscovery();
  }

  void _startDiscovery() {
    _discoveryStreamSubscription =
        FlutterBluetoothSerial.instance.startDiscovery().listen((r) {
      setState(() {
        Iterator i = devices.iterator;
        while (i.moveNext()) {
          var _device = i.current;
          if (_device.device == r.device) {
            _device.availability = _DeviceAvailability.yes;
            _device.rssi = r.rssi;
          }
        }
      });
    });

    _discoveryStreamSubscription.onDone(() {
      setState(() {
        _isDiscovering = false;
      });
    });
  }

  @override
  void dispose() {
    // Avoid memory leak (`setState` after dispose) and cancel discovery
    _discoveryStreamSubscription.cancel();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    List<DeviceTile> list = devices
        .map(
          (_device) => DeviceTile(
            device: _device.device,
            // rssi: _device.rssi,
            // enabled: _device.availability == _DeviceAvailability.yes,
            onTap: () {
              widget.onChatPage?.call(_device.device);
            },
          ),
        )
        .toList();
    return ListView(
      children: list,
    );
  }
}
