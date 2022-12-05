// Example of digital input using the M5Stack dual-button unit with M5Core-Ink board

#include "M5CoreInk.h"          // M5Core-Ink library

const int blueButtonPin = 33;  
int blueButtonVal = HIGH;
int blueButtonLast = HIGH;

const int redButtonPin = 32;  
int redButtonVal = HIGH;
int redButtonLast = HIGH;

unsigned long buttonTimer = 0;

void setup() {
  M5.begin();
  Serial.begin(9600);
  Serial.println("M5Core-Ink Dual-Button Unit Example");
  
  pinMode(blueButtonPin, INPUT);
  pinMode(redButtonPin, INPUT);
}

void loop() {

  // read button inputs every 100ms:
  if(millis() > buttonTimer + 100) {
    
    blueButtonVal = digitalRead(blueButtonPin);
    
    if(blueButtonVal != blueButtonLast) {
      Serial.print("blue button: ");
      Serial.println(blueButtonVal);
      blueButtonLast = blueButtonVal;
    }
    
    redButtonVal = digitalRead(redButtonPin);
    
    if(redButtonVal != redButtonLast) {
      Serial.print("red button: ");
      Serial.println(redButtonVal);
      redButtonLast = redButtonVal;
    }
    
    buttonTimer = millis();
  }
  
  M5.update();
}