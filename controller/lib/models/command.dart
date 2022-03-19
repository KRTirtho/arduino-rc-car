class Command {
  final String title;
  final String _command;

  Command(this.title, this._command);

  List<int> get command => _command.codeUnits;
}
