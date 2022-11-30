// M5Stack-CoreInk RTC (Real Time Clock) API documentation:
// https://docs.m5stack.com/en/api/coreink/rtc
// this example prints RTC time to the Serial port
// RTC time can be set with hh:mm:ss sent via Serial 

#include "M5CoreInk.h"

RTC_TimeTypeDef RTCtime;
RTC_DateTypeDef RTCDate;

char timeStrBuf[64];
int rtcSeconds;
unsigned long rtcTimer;

void setup() {
  M5.begin();
  Serial.begin(9600);  
  delay(1000);

  /*
  // set RTC date (do one time when needed):
  RTCDate.Year = 2022;
  RTCDate.Month = 11;
  RTCDate.Date = 26;
  M5.rtc.SetDate(&RTCDate);
  */

  // read RTC date and print it to the Serial port:
  M5.rtc.GetDate(&RTCDate);
  sprintf(timeStrBuf, "RTCDate = %d/%02d/%02d",
    RTCDate.Year, RTCDate.Month, RTCDate.Date);
  Serial.println(timeStrBuf);

  rtcSeconds = RTCtime.Seconds;
}

void loop() {
  // check if data has been received on the Serial port:
  if(Serial.available() > 0)
  {
    char input[9];
    int charsRead = Serial.readBytes(input, 9);    
    // input format is "hh:mm:ss" + new line character (9 chars total)  
    if(charsRead == 9 && input[2] == ':' && input[5] == ':') {
      // convert ASCII input characters to numbers
      int ss = int(input[6] - '0') + int(input[7] - '0') * 10; 
      Serial.print("seconds: ");
      Serial.println(ss);
      RTCtime.Seconds = ss;
      int mm = int(input[4] - '0') + int(input[3] - '0') * 10; 
      Serial.print("minutes: ");
      Serial.println(mm);
      RTCtime.Minutes = mm;
      int hr = int(input[1] - '0') + int(input[0] - '0') * 10; 
      Serial.print("hours: ");
      Serial.println(hr);
      RTCtime.Hours = hr;
      M5.rtc.SetTime(&RTCtime);      // set RTC time
    }
    else {
      Serial.print("received wrong time format.. ");
      Serial.println(input);
    }
  }

  // check timer every 100 ms:
  if(millis() > rtcTimer + 100) {
    M5.rtc.GetTime(&RTCtime);
    // check if RTC seconds value changed:
    if(rtcSeconds != RTCtime.Seconds) {
      // print RTC time to the Serial port:
      sprintf(timeStrBuf,"RTCtime = %02d:%02d:%02d",
        RTCtime.Hours, RTCtime.Minutes, RTCtime.Seconds);
      Serial.println(timeStrBuf);
      rtcSeconds = RTCtime.Seconds;
    }
    rtcTimer = millis();
  }
  M5.update();
}