[Arduino Editor Link](https://create.arduino.cc/editor/n-p/b86a3e53-a7d1-47c5-adc6-be6b12d8baee/preview)

This example uses the [ESP32Servo library](https://github.com/jkb-git/ESP32Servo) by John K. Bennett and Kevin Harrington.  In Arduino IDE, select `Tools -> Manage Libraries...` and search for `ESP32Servo` to install the library.   

To test the example, connect a servo to the neighboring pins `GND`, `5V` and `G26` on M5Core-Ink board (top connector).  Move the board's built-in side scroll wheel up or down to actuate the servo.   

NOTE: Sometimes a servo may start to vibrate after moving to its maximum rotation at 0 or 180 degrees.  Adjust the angle of rotation in code to address the issue if needed.
