// Example of controlling the M5Stack RGB LED Unit (U003)
// with the M5Stack-CoreInk board

#include <Adafruit_NeoPixel.h>
#include "M5CoreInk.h" 

const int rgbledPin = 32;   // bottom connector output pin (G32)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    3,                      // number of pixels 
    rgbledPin,              // pin number
    NEO_GRB + NEO_KHZ800);  // LED type

unsigned long fadeTimer = 0;

int redVal, redValFinal;
int greenVal, greenValFinal;
int blueVal, blueValFinal;

void setup() {
  M5.begin();        
  Serial.begin(9600);
  pixels.begin();  
  pixels.setBrightness(50); // set brightness to about 1/5 (max = 255)

  redVal = 0;
  greenVal = 0;
  blueVal = 0;

  redValFinal = 255;
  greenValFinal = 255;
  blueValFinal = 255;
}

void loop() {

  // check if data has been received on the Serial port:
  if (Serial.available() > 0) {
    // read red, green and blue color values:
    redValFinal = Serial.parseInt();   // read the first value as an integer
    Serial.read();  // read the comma character (,)
    greenValFinal = Serial.parseInt(); // read the second value as an integer
    Serial.read();  // read the comma character (,)
    blueValFinal = Serial.parseInt();  // read the third value as an integer
    Serial.read();  // read the newline character (\n)

    // print the received values:
    Serial.print("Received: ");
    Serial.print(redValFinal);
    Serial.print(", ");
    Serial.print(greenValFinal);
    Serial.print(", ");
    Serial.println(blueValFinal);
  }

  if(millis() > fadeTimer + 10) {  // 10 ms passed    
    // increment color values:
    if(redValFinal > redVal)
      redVal++;
    else if(redValFinal < redVal)
      redVal--;
    if(greenValFinal > greenVal)
      greenVal++;
    else if(greenValFinal < greenVal)
      greenVal--;
    if(blueValFinal > blueVal)
      blueVal++;
    else if(blueValFinal < blueVal)
      blueVal--;
    
    // set pixel colors:
    for(int i=0; i<3; i++) {
      pixels.setPixelColor(i, redVal, greenVal, blueVal);
    } 
    pixels.show(); 
    
    fadeTimer = millis();   // update timer
  }
}