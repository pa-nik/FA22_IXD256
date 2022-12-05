## Sensor (Analog Input) Example   

[Arduino Editor Link](https://create.arduino.cc/editor/n-p/dabf0324-4597-484a-96cc-41aee3f9c7de/preview)   

This example can be used with M5Stack modules like the potentiometer [Angle Unit](https://docs.m5stack.com/en/unit/angle), photoresistor [Light Unit](https://docs.m5stack.com/en/unit/light), or other analog sensors.  

ESP32 microprocessor in the M5Stack Core Ink board features a 12-bit Analog-to-Digital Converter (ADC), which can digitize a voltage level from a sensor or other analog input connected to a pin.  In arduino code this is done with the `analogRead()` function, which returns a value in the range 0 - 4095.

The example code shows how to use the `map()` function to change the input value to 0 - 255 (8-bit) range to control the brightness of the built-in LED using Pulse Width Modulation (PWM) with the `analogWrite()` function.  The input value is also printed to the Serial port every 100ms, using a timer variable.
 
