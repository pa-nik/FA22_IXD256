// Example of reading 3 input values with p5.webserial:
// https://github.com/yoonbuck/p5.WebSerial

const serial = new p5.WebSerial();

var portButton;  // serial port button
var showButton;  // variable to show/hide the port button
var inData;      // variable for incoming serial data
var accX;        // accelerometer X value
var accY;        // accelerometer Y value
var accZ;        // accelerometer Z value
var accXData = [];   // accelerometer X values array
var dataCounter = 0; // array index counter

function setup() {
  createCanvas(300, 300);
   // check to see if serial is available:
   if (!navigator.serial) {
    alert("WebSerial is not supported in this browser. \
           Try Chrome or MS Edge.");
  }
  // check for any ports that are available:
  serial.getPorts();
  // if there's no port chosen, choose one:
  serial.on("noport", makePortButton);
  // open whatever port is available:
  serial.on("portavailable", openPort);
  // handle serial errors:
  serial.on("requesterror", portError);
  // handle any incoming serial data:
  serial.on("data", serialEvent);
  serial.on("close", makePortButton)
  // add serial connect/disconnect listeners:
  navigator.serial.addEventListener("connect", portConnect);
  navigator.serial.addEventListener("disconnect", portDisconnect);
}

// if there's no port selected,
// make a port select button appear:
function makePortButton() {
  // create and position a port chooser button:
  portButton = createButton("choose port");
  portButton.position(30, height-30);
  // give the port button a mousepressed handler:
  portButton.mousePressed(choosePort);
  showButton = true;
}

// make the port selector window appear:
function choosePort() {
  if (portButton) portButton.show();
  serial.requestPort();
}

function draw() {
  background(0);
  fill(255);
  noStroke();
  text("accX: " + accX, 20, 30);
  text("accY: " + accY, 20, 45);
  text("accZ: " + accZ, 20, 60);

  // map values from range -10 - 10 to 0 - 255
  var r = map(accX, -10, 10, 0, 255)
  var g = map(accY, -10, 10, 0, 255)
  var b = map(accZ, -10, 10, 0, 255)

  // draw a circle with accelerometer data as color
  fill(r, g, b);
  ellipse(width/2, height/2, 100, 100);

  // draw a graph of accXData array:
  stroke(255);
  for (var i = 1; i < width; i++)
    line(i, height/2 + accXData[i-1] * 5,
         i, height/2 + accXData[i] * 5);

  fill(255);
  if(!showButton) {
    text("press 'p' to show/hide serial port button",
         20, height-20);
  }
}

// open the selected port, and make the port
// button invisible:
function openPort() {
  // wait for the serial.open promise to return,
  // then call the initiateSerial function
  serial.open().then(initiateSerial);

  // once the port opens, let the user know:
  function initiateSerial() {
    console.log("port open");
  }
  // hide the port button once a port is chosen:
  if (portButton) portButton.hide();
}

// pop up an alert if there's a port error:
function portError(err) {
  alert("Serial port error: " + err);
}
// read any incoming data as a string
// (assumes a newline at the end of it):
function serialEvent() {
  //inData = Number(serial.read());
  inData = serial.readStringUntil('\n');
  if(inData != null && inData.length > 0) {
    print(inData);
    var values = split(inData, ', ');
    if (values.length >= 3) {
      accX = Number(values[0]);
      accY = Number(values[1]);
      accZ = Number(values[2]);

      accXData[dataCounter] = accX;  // add last reading
      if(dataCounter < width)
        dataCounter += 1;
      else
        dataCounter = 0;
    }
  }
}

// try to connect if a new serial port
// gets added (i.e. plugged in via USB):
function portConnect() {
  console.log("port connected");
  serial.getPorts();
}

// if a port is disconnected:
function portDisconnect() {
  serial.close();
  console.log("port disconnected");
}

function closePort() {
  serial.close();
}

function keyPressed() {
  if(key == 'p') {
    if (!portButton) {
      makePortButton();
    }
    else if (showButton) {
      portButton.hide();
      showButton = false;
    }
    else {
      portButton.show();
      showButton = true;
    }
  }
}
