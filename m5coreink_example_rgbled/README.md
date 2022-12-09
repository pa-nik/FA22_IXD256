## RGB LED Unit Example   

[Arduino Editor Link](https://create.arduino.cc/editor/n-p/53327a49-cbe3-46b1-8440-cd6443039b33/preview)   

This example shows how to use the [M5Stack RGB LED Unit (U003)](https://docs.m5stack.com/en/unit/rgb) with the Adafruit_NeoPixel library.  This plug-in module features 3 individually-controllable SK6812 LEDs.  If you are using an LED strip with these or compatible LEDs (such as WS2812b), adjust the number of pixels parameter of the `Adafruit_NeoPixel` object.   

The code includes variables for each color component to fade the LED colors gradually using a timer.  The RGB values can be set by sending 3 comma-separated numbers over the Serial port.  

 [Adafruit NeoPixel Überguide](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use) is a good resource for additional instructions on controlling the SK6812, WS2812 and other "smart" LEDs.
