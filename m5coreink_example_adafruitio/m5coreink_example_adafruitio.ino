#include "arduino_secrets.h"
// Example of sending and receiving MQTT messages via AdafruitIO

#include <WiFi.h>
#include <AdafruitIO_WiFi.h>
#include "M5CoreInk.h" 

// initialize WiFi connection:
WiFiClient wifi;
AdafruitIO_WiFi io(SECRET_AIO_USERNAME, SECRET_AIO_KEY, SECRET_SSID, SECRET_PASS);
AdafruitIO_Feed *sensorFeed = io.feed("sensorfeed");
AdafruitIO_Feed *ledFeed = io.feed("ledfeed");

const int ledPin = 10;          // built-in LED pin (G10)
const int sensorPin = 33;       // bottom connector input pin (G33)

unsigned long sensorTimer = 0;

void setup() {
  M5.begin();
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the ledFeed:
  ledFeed->onMessage(handleMessage);
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  ledFeed->get();

  // print connection status
  Serial.println(io.statusText());
}

void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
  // publish message every 2 seconds:
  if(millis() > sensorTimer + 2000) {

    // read a 12-bit sensor value:
    int sensorVal = analogRead(sensorPin);  

    // print sensorVal to Serial port:
    Serial.print("send sensorVal: ");
    Serial.println(sensorVal);

    sensorFeed->save(sensorVal);
    
    sensorTimer = millis();
  }
}

void handleMessage(AdafruitIO_Data *data) {
 
  Serial.print("received: ");
  Serial.println(data->value());
  
  if(strcmp((char*)data->value(), "ON")) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}