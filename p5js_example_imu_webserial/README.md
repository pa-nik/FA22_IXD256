## IMU Visualization (WebSerial) Example   

[P5.js Editor Link](https://editor.p5js.org/panik/sketches/6pzIHUndW)  

This p5.js sketch shows a visualization of a circle that changes color in response to 3 Inertial Measurement Unit (IMU) values received over a WebSerial connection.  The IMU chip incorporates an accelerometer and gyroscope, providing 6 Degrees of Freedom (6-DOF): X, Y and Z acceleration + X, Y and Z gyroscope data.  

The first 3 of these values (`accX`, `accY`, `accZ`) are mapped to RGB colors of a circle.  In addition, a line graph spanning the width of the sketch shows the `accX` value changing over time.   

To test this sketch, program the M5 board with the [IMU Example](../m5coreink_example_imu/).  Open the P5.js Editor Link above and check that the values are being received.  The Serial port connection can be changed by pressing the 'p' key to show/hide the `choose port` button.   

NOTE: Only one Serial connection to a specific port can be open on the computer at a time.  If you have Serial Monitor open in the Arduino Editor, close it before opening the p5.js sketch.   
