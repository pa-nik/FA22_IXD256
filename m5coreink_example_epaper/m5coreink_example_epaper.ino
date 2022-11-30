// M5Stack-CoreInk E-Ink API documentation:
// https://docs.m5stack.com/en/api/coreink/eink_api

#include "M5CoreInk.h"             

Ink_Sprite PageSprite(&M5.M5Ink);  // e-ink display sprite

int buttonCounter = 0;

void setup() {
  M5.begin();
  Serial.begin(9600);

  // initialize e-ink display:
  if( M5.M5Ink.isInit()){  
  
    M5.M5Ink.clear(); //clear the screen. 
    delay(1000);
    //create e-ink sprite
    if( PageSprite.creatSprite(0, 0, 200, 200,true) != 0 ) {
      Serial.printf("Ink Sprite create failed");
    }
    PageSprite.drawString(10, 10, "HELLO E-PAPER!");
    PageSprite.pushSprite();  // display the sprite
  }
  else {
    Serial.println("Ink Init failed");
  }
}

void loop() {
  // side button press: draw to portion of the screen
  if( M5.BtnPWR.wasPressed()) {
    char buf[80]; // character buffer
    // print buttonCounter value to character buffer:
    sprintf(buf, "buttonCounter = %d", buttonCounter);   
    buttonCounter++; // increment buttonCounter 
    PageSprite.FillRect(10, 25, 100, 10, 1); // draw white rectangle
    PageSprite.drawString(10, 25, buf);  // draw character buffer
    PageSprite.pushSprite(); 
  }
  // top button press: refresh entire screen
  if( M5.BtnEXT.wasPressed()) {
    M5.M5Ink.clear();
    PageSprite.clear(CLEAR_DRAWBUFF | CLEAR_LASTBUFF);
    PageSprite.drawString(10, 10, "HELLO E-PAPER!");
    PageSprite.pushSprite();  
  }
  M5.update();
}