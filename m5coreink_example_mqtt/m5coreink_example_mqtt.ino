// Example of receiving (subscribing to) and sending (publishing) MQTT messages
// fill in SECRET_SSID and SECRET_PASS in Secret tab to connect to the network

#include "arduino_secrets.h"
#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include "M5CoreInk.h" 

// initialize WiFi connection:
WiFiClient wifi;
MqttClient mqttClient(wifi);

// details for MQTT client:
//const char broker[] = "public.cloud.shiftr.io";
const char broker[] = "test.mosquitto.org";
int port = 1883;

char input_topic[] = "input_topic_name";
char output_topic[] = "output_topic_name";

const int ledPin = 10;          // built-in LED pin (G10)
const int sensorPin = 33;       // bottom connector input pin (G33)

unsigned long mqttPublishTimer = 0;

void setup() {
  M5.begin();
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  // initialize WiFi, if not connected:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(SECRET_SSID);
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(2000);
  }
  // print IP address once connected:
  Serial.print("Connected. My IP address: ");
  Serial.println(WiFi.localIP());

  // set the credentials for the MQTT client:
  //char clientID[] = "testClient";
  //mqttClient.setId(clientID);
  //mqttClient.setUsernamePassword("public", "public");

  // try to connect to the MQTT broker once you're connected to WiFi:
  while (!connectToBroker()) {
    Serial.println("attempting to connect to broker");
    delay(1000);
  }
  Serial.println("connected to broker");

  // subscribe to topic:
  mqttClient.subscribe(output_topic);

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);
}

void loop() {
  // if not connected to the broker, try to connect:
  if (!mqttClient.connected()) {
    Serial.println("reconnecting");
    connectToBroker();
  }

  // receive message:
  if (mqttClient.parseMessage() > 0) {
    
  }
  
  // publish message every second:
  if(millis() > mqttPublishTimer + 1000) {

    // read a 12-bit sensor value:
    int sensorVal = analogRead(sensorPin);  

    // print sensorVal to Serial port:
    Serial.print("send sensorVal: ");
    Serial.println(sensorVal);

    // publish sensorVal to mqtt topic:
    mqttClient.beginMessage(input_topic);
    mqttClient.print(sensorVal);
    mqttClient.endMessage();

    mqttPublishTimer = millis();
  }
}

void onMqttMessage(int messageSize) {
  Serial.print("Received a message on topic: ");
  Serial.println(mqttClient.messageTopic());
  Serial.print("message length: ");
  Serial.println(messageSize);
  
  Serial.print("message data: ");
  while (mqttClient.available()) {
    char inChar = (char)mqttClient.read();
    Serial.println(inChar);
    if(inChar == '0')
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);
  }
}

boolean connectToBroker() {
  // if the MQTT client is not connected:
  if (!mqttClient.connect(broker, port)) {
    // print out the error message:
    Serial.print("MOTT connection failed. Error no: ");
    Serial.println(mqttClient.connectError());
    // return that you're not connected:
    return false;
  }
  return true;
}