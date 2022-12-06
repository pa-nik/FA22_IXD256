## Sensor Visualization (WebSerial) Example   

[P5.js Editor Link](https://editor.p5js.org/panik/sketches/LjvScKOEU)  

This p5.js sketch shows a simple visualization of a circle that changes brightness in response to a value received over a WebSerial connection.  The expected value is a 12-bit number (0 - 4095 range) that is mapped to 8 bits (0 - 256 range) in order to use it as a parameter of the `fill()` function.

In order to test this sketch, program the M5 board with code that outputs one value to the Serial port, such as the [Sensor Example](../m5coreink_example_sensor/).  Open the P5.js Editor Link above and check that the value is being received.  The Serial port connection can be changed by pressing the 'p' key to show/hide the `choose port` button.

NOTE: Only one Serial connection to a specific port can be open on the computer at one time.  If you have Serial Monitor open in the Arduino Editor, close it before opening the p5.js sketch.
