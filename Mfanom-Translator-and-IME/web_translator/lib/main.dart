import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:flutter/widgets.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Mfanom Translator',
      theme: ThemeData(
        useMaterial3: false,
        disabledColor: const Color(0xFF000000),
      ),
      home: const MyHomePage(title: 'Flutter Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final TextEditingController _controller = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xFFFDF6E3),
      body: Center(
        child: Row (
          children: [
            const Padding(  padding: EdgeInsets.only(left:125)),

            Column (
              children: <Widget> [
                const Padding(  padding: EdgeInsets.only(top:150)),

                const Text(
                  'Mfanom',
                  style: TextStyle(color: Color(0xFF000000)),
                ),

                const Padding(  padding: EdgeInsets.only(top:20)),

                SizedBox(
                  height: 300,
                  width: 300,
                  child: 
                    TextField(
                      maxLines: 10,
                      onChanged: (text) {
                        setState(() {
                          _controller.text = text;
                        }); 
                      },
                      cursorColor: const Color(0xFF000000),
                      decoration: InputDecoration(
                        focusedBorder: OutlineInputBorder(borderSide: const BorderSide(color: Color(0x66000000)), borderRadius: BorderRadius.circular(10)),
                        border: OutlineInputBorder(borderRadius: BorderRadius.circular(10)),
                        hintText: 'Enter Text',
                        hintStyle: const TextStyle(color: Color(0x88000000)),
                      ),
                    ),
                ),
              ],
            ),

            const Spacer(),

            Column (
              children: <Widget> [
                const Padding(  padding: EdgeInsets.only(top:150)),

                const Text(
                  'English',
                  style: TextStyle(color: Color(0xFF000000)),
                ),

                const Padding(  padding: EdgeInsets.only(top:20)),

                SizedBox(
                  height: 300,
                  width: 300,
                  child: 
                    TextField(
                      maxLines: 10,
                      controller: _controller,
                      readOnly: true,
                      decoration: InputDecoration(
                        focusedBorder: OutlineInputBorder(borderSide: const BorderSide(color: Color(0x66000000)), borderRadius: BorderRadius.circular(10)),
                        border: OutlineInputBorder(borderRadius: BorderRadius.circular(10)),
                        hintText: 'Translation',
                      ),
                    ),
                ),
              ],
            ),

            const Padding(  padding: EdgeInsets.only(right:125)),
          ],
        ),
      ),
      // floatingActionButton: FloatingActionButton(
      //   backgroundColor: const Color(0xFFFFFFFF),
      //   onPressed: _incrementCounter,
      //   tooltip: 'Increment',
      //   child: const Icon(Icons.add),
      // ),
    );
  }
}
