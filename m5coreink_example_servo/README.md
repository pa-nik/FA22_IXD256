This example uses the [ESP32Servo](https://github.com/jkb-git/ESP32Servo) library by John K. Bennett and Kevin Harrington.  In Arduino IDE, select `Tools -> Manage Libraries...`, search for and install `ESP32Servo`.   

[Arduino Editor Link](https://create.arduino.cc/editor/n-p/b86a3e53-a7d1-47c5-adc6-be6b12d8baee/preview)

To test the example, connect a servo to the neighboring pins `GND`, `5V` and `G26` on M5Core-Ink board (top connector).  Sometimes a servo may start to vibrate after moving to its maximum rotation at 0 or 180 degrees.  Adjust the angle to address the issue if needed.
