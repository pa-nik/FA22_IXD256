## Adafruit IO Publish and Subscribe   

[Arduino Editor Link](https://create.arduino.cc/editor/n-p/c3c109ac-8f50-4f57-96f9-67ff6c52fa50/preview)   

This example shows how to use the [Adafruit IO](https://io.adafruit.com/) cloud platform.   Like other Internet of Things (IoT) services, Adafruit IO offers a range of useful features, such as dashboards, graphs, and alerts, that make it easy to monitor and control data in real-time.  Most importantly it offers a free plan for you to create your own "feeds" of data that can be updated up to 30 times a minute.

Each Adafruit IO feed represents a stream of data from a connected device or sensor, and can store a series of data points over time. Adafruit IO feeds are designed to be flexible and can store data of various types, such as numbers, strings, or even complex JSON objects.

The communication with Adafruit IO feeds is accomplished via MQTT and Adafruit provides the necessary functionality as part of its `AdafruitIO_WiFi` library.  In order to connect to a feed that you create on io.adafruit.com, configure the Secret tab in Arduino Editor (or arduino_secrets.h in Arduino IDE) with settings for `SECRET_AIO_USERNAME` and `SECRET_AIO_KEY`.  

You will also need to configure the WiFi network name and password with `SECRET_SSID` and `SECRET_PASS` settings.  Don't forget that these will change when you work at school or at home.  

In this example, 3 separate `AdafruitIO_Feed` variables are created for subscribing and publishing data to Adafruit IO.  The first is the `sensorFeed` that publishes sensor readings obtained with `analogRead()` on M5Stack-CoreInk bottom connector pin `G33` (so this example can be used with M5Stack units like [Angle](https://docs.m5stack.com/en/unit/angle) or [Light](https://docs.m5stack.com/en/unit/light)).  

The `sensorFeed` is configured to connect to the following feed on Adafruit IO (which has its "sharing" setting set to be public in order to be viewable by anyone):  
[Feed: "sensorfeed"](https://io.adafruit.com/pa_nik/feeds/sensorfeed)

**NOTE:** During wireless operation, some of the analog inputs on the ESP32 microprocessor are not available.  For example, the `G26` and `G25` pins on the M5Stack-CoreInk board will no work with the `analogRead()` function.  Instead, choose `G33` (4-pin bottom connector) or `G36` (top connector).  

The second `AdafruitIO_Feed` in the code is the `ledFeed` that subscribes to "ON" and "OFF" messages controlling the built-in LED on pin `G10`.  These messages are in turn published to the Adafruit IO feed by a dashboard with a toggle switch.  The feed and dashboard links (both set to be public):  
[Feed: "ledfeed"](https://io.adafruit.com/pa_nik/feeds/ledfeed)  
[Dashboard: "leddash"](https://io.adafruit.com/pa_nik/dashboards/leddash)  

The third `AdafruitIO_Feed` in this example is the `colorFeed` that subsribes to messages representing RGB colors in hex format (such as #FF0000 for red color).  The Adafruit library makes it easy to convert the received message to color by calling `data->toNeoPixel()` method of the `AdafruitIO_Data` object containing the feed data.  The color is then used to light up the pixels of the [RGB LED Unit](https://docs.m5stack.com/en/unit/rgb) connected to the bottom connector pin `G32` on M5Stack-CoreInk.   
[Feed: "colorfeed"](https://io.adafruit.com/pa_nik/feeds/colorfeed)  
[Dashboard: "colorpick"](https://io.adafruit.com/pa_nik/dashboards/colorpick)  
