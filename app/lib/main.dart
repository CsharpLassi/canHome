import 'dart:async';
import 'package:flutter/material.dart';
import 'package:led_control/helper_methods.dart';
import 'package:quick_actions/quick_actions.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'LED Strip Control',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'LED Strip Control'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);
  final String title;

  @override
  _MyHomePageState createState() => new _MyHomePageState();
}

class RGB {
  int r = 0;
  int g = 0;
  int b = 0;

  double get dr => r.toDouble();
  double get dg => g.toDouble();
  double get db => b.toDouble();
  String get hr => _toRadixBase16(r);
  String get hg => _toRadixBase16(g);
  String get hb => _toRadixBase16(b);

  set dr(double val) {
    r = val.toInt();
  }

  set dg(double val) {
    g = val.toInt();
  }

  set db(double val) {
    b = val.toInt();
  }

  String _toRadixBase16(int val) {
    String ret = val.toRadixString(16);
    if (ret.length == 1) ret = "0" + ret;
    return ret;
  }

  RGB();

  RGB.rgb(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
  }


  RGB.color(Color c) {
    RGB.rgb(c.red, c.green, c.blue);
  }
}

class _MyHomePageState extends State<MyHomePage> {
  double brightness = 255.0;
  double delay = 30.0;
  static const int colordelay = 50;
  DateTime dateTime = DateTime.now();
  RGB rgb = new RGB();
  String debug = "";

  int get idelay => delay.toInt();
  int get ibrightness => brightness.toInt();

  @override
  void initState() {
    super.initState();
    final QuickActions quickActions = const QuickActions();
    quickActions.initialize((String shortcutType) {
      if (shortcutType == 'Off')
        turnLedOff();
      else if (shortcutType == 'On')
        turnLedOn();
    });
    quickActions.setShortcutItems(<ShortcutItem>[
      const ShortcutItem(type: 'On', localizedTitle: 'On', icon: 'AppIcon'),
      const ShortcutItem(type: 'Off', localizedTitle: 'Off', icon: 'AppIcon'),
    ]);
  }

  Future turnLedOn() async {
    return HelperMethods.get("led/on", context);
  }

  Future turnLedOff() async {
    return HelperMethods.get("led/off", context);
  }


  Future changeColor() async {
    return HelperMethods.get("led/set?color=x${rgb.hr+rgb.hg+rgb.hb}", context);
  }

  Future changeMaxBrightness(int brightness) async {
    return HelperMethods.get("led/set?brightness=x${brightness.toRadixString(16)}", context);
  }

  Future resetConnection() async {
    return HelperMethods.get("resetConnection/", context);
  }


  void sliderChange(Function f, int dateTimeMilliseconds, [int val]) {
    if (DateTime.now().isAfter(dateTime.add(new Duration(milliseconds: dateTimeMilliseconds)))) {
      Function.apply(f, val == null ? [] : [val]);
      dateTime = DateTime.now();
    }
  }

  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: AppBar(
        title: new Text(widget.title),
      ),
      body: ListView(
        children: <Widget>[
          new ListTile(
            title: new MaterialButton(
              child: const Text(
                'On',
              ),
              onPressed: turnLedOn,
            ),
          ),
          new ListTile(
            title: new MaterialButton(
              child: const Text(
                'Off',
              ),
              onPressed: turnLedOff,
            ),
          ),
          new ExpansionTile(
            title: const Text(
              'SingleColor',
            ),
            children: <Widget>[
              new ListTile(
                subtitle: new Text("Red: ${rgb.hr} | ${rgb.r}"),
                title: new Slider(
                  value: rgb.dr,
                  onChanged: (d) {
                    setState(() => rgb.dr = d);
                    sliderChange(changeColor, colordelay);
                  },
                  min: 0.0,
                  max: 255.0,
                  label: 'R',
                ),
              ),
              new ListTile(
                subtitle: new Text("Green: ${rgb.hg} | ${rgb.g}"),
                title: new Slider(
                  value: rgb.dg,
                  onChanged: (d) {
                    setState(() => rgb.dg = d);
                    sliderChange(changeColor, colordelay);
                  },
                  min: 0.0,
                  max: 255.0,
                  label: 'G',
                ),
              ),
              new ListTile(
                subtitle: new Text("Blue: ${rgb.hb} | ${rgb.b}"),
                title: new Slider(
                  value: rgb.db,
                  onChanged: (d) {
                    setState(() => rgb.db = d);
                    sliderChange(changeColor, colordelay);
                  },
                  min: 0.0,
                  max: 255.0,
                  label: 'B',
                ),
              ),
              new Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: <Widget>[
                  new Text(
                    'Color: ${rgb.hb+rgb.hg+rgb.hr}',
                  ),
                  new MaterialButton(
                    child: new Text(
                      'SingleColor',
                    ),
                    //onPressed: toggleSingleColor,
                  ),
                ],
              )
            ],
          ),

          new ListTile(
            subtitle: new Text("Brightness ${brightness.toInt().toString()}"),
            title: new GestureDetector(
              child: new Slider(
                value: brightness,
                onChanged: (d) {
                  setState(() => brightness = d);
                  sliderChange(changeMaxBrightness, 100, ibrightness);
                },
                min: 0.0,
                max: 255.0,
                label: '${brightness.round()}',
              ),
            ),
          ),
        ],
      ),
    );
  }
}
