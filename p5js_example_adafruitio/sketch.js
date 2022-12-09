// Example of reading a value from an Adafruit IO feed
// NOTE: the feed must be made public with "Sharing" setting

var feedURL = "https://io.adafruit.com/api/v2/pa_nik/feeds/sensorfeed/"

var feedVal;  // value obtained from the feed
var feedTimer = 0;

function setup() {
  createCanvas(300, 300);
}

function aioGetData(aioJsonData)
{
  //print(aioJsonData);
  feedVal = aioJsonData.last_value;
  print(feedVal);
}

function draw() {
  background(0);
  fill(255);
  text("feed value: " + feedVal, 20, 30);
  // map the value from 0-4095 to 0-255 range:
  brightnessVal = map(feedVal, 0, 4095, 0, 255)
  fill(brightnessVal);
  ellipse(width/2, height/2, 100, 100);
  
  if(millis() > feedTimer + 1000) {
    loadJSON(feedURL, aioGetData);
    feedTimer = millis();
  }
}