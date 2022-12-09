#include "arduino_secrets.h"
// Example of sending and receiving MQTT messages via AdafruitIO

#include <WiFi.h>
#include <AdafruitIO_WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "M5CoreInk.h" 

// initialize WiFi connection:
WiFiClient wifi;
AdafruitIO_WiFi io(SECRET_AIO_USERNAME, SECRET_AIO_KEY, SECRET_SSID, SECRET_PASS);
AdafruitIO_Feed *sensorFeed = io.feed("sensorfeed");
AdafruitIO_Feed *ledFeed = io.feed("ledfeed");
AdafruitIO_Feed *colorFeed = io.feed("colorfeed");

const int ledPin = 10;          // built-in LED pin (G10)
const int sensorPin = 33;       // bottom connector input pin (G33)
const int rgbledPin = 32;   // bottom connector output pin (G32)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    3,                      // number of pixels 
    rgbledPin,              // pin number
    NEO_GRB + NEO_KHZ800);  // LED type

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
  ledFeed->onMessage(toggleMessage);

  // set up a message handler for the colorFeed:
  colorFeed->onMessage(colorMessage);
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  ledFeed->get();
  colorFeed->get();

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

void toggleMessage(AdafruitIO_Data *data) {
 
  Serial.print("toggleMessage received: ");
  Serial.println(data->value());
  
  if(strcmp((char*)data->value(), "ON")) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}

void colorMessage(AdafruitIO_Data *data) {
 
  Serial.print("colorMessage received: ");
  Serial.println(data->value());

  long color = data->toNeoPixel();
  for (int i = 0; i < 3; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}