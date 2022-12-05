// Example of reading analog input with the M5Stack Core Ink board

#include "M5CoreInk.h"          

const int ledPin = 10;          // built-in LED pin (G10)
const int sensorPin = 33;       // bottom connector input pin (G33)

int sensorVal = 0;
int brightnessVal = 0;

unsigned long sensorTimer = 0;

void setup() {
  M5.begin();
  Serial.begin(9600);
  Serial.println("M5Core-Ink Sensor Example");
  
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {

  // read button inputs every 100ms:
  if(millis() > sensorTimer + 100) {
    
    // read a 12-bit sensor value:
    sensorVal = analogRead(sensorPin);  
    
    // print sensorVal to the Serial port:
    Serial.println(sensorVal);
    
    // map sensorVal from range 0 - 4095 (12 bits) to 0 - 255 (8 bits):
    brightnessVal = map(sensorVal, 0, 4095, 0, 255);
    
    // set built-in LED brightness using PWM:
    analogWrite(ledPin, brightnessVal);
    
    sensorTimer = millis();
  }
  
  M5.update();
}