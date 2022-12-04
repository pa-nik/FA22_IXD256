// Example of controlling a servo using the scroll wheel on M5Core-Ink

#include "M5CoreInk.h"          // M5Core-Ink library
#include <Servo.h>              // Servo library

const int servoPin = 26;        // Servo pin
Servo servoObj;                 // Servo object 
int servoVal = 0;               // Servo output value

void setup() {
  M5.begin();
  Serial.begin(9600);
  Serial.println("M5Core-Ink Servo Example");
  
  servoObj.attach(servoPin);    // attach Servo to servoPin
}

void loop() {

  if(M5.BtnUP.wasPressed()) {   // scroll wheel up button
    servoVal = 0;
    servoObj.write(servoVal);
    Serial.print("move servo to 0");
    Serial.println(servoVal);
  }
  else if(M5.BtnDOWN.wasPressed()) {   // scroll wheel down button
    servoVal = 180;
    servoObj.write(servoVal);
    Serial.println("move servo to 180");
  }
  
  M5.update();
}