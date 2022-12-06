## MQTT Example   

[Arduino Editor Link](https://create.arduino.cc/editor/n-p/8c9e5716-e0a4-4816-899a-176a80aca9e0/preview)   

This example shows how to receive and send messages using the [Message Queuing Telemetry Transport (MQTT)](https://en.wikipedia.org/wiki/MQTT), a lightweight messaging protocol commonly used in the field of Internet of Things (IoT) to connect devices and systems.  

MQTT is based on a publish-subscribe model, in which clients can publish messages to a broker (server) and other clients can subscribe to the broker to receive those messages. The broker routes the messages to the appropriate subscribers, based on the topic of the message. This allows clients to send and receive messages without needing to establish direct connections with each other.  

To use the sketch, first fill in the `SECRET_SSID` and `SECRET_PASS` fields with the WiFi network name and password.  These settings are available in the Secret tab in the online Arduino Editor or arduino_secrets.h tab in Arduino IDE.

The code uses a timer to publish `sensorVal` variable once a second to the MQTT `input_topic` and subscribes to `output_topic` to receive messages (the expected messages are '0' or '1' to turn the built-in LED on and off).

The default MQTT `broker` is set to [test.mosquitto.org](https://test.mosquitto.org/).  Another free public MQTT broker that may be used as an alternative is [public.cloud.shiftr.io](https://public.cloud.shiftr.io/).    
