// MQTT client details:
var broker = {
  //hostname: 'public.cloud.shiftr.io',
  //port: 443  
  hostname: 'test.mosquitto.org',
  port: 8081   
};
// MQTT client:
var client;
// client credentials:
var creds = {
    clientID: 'p5Client',
    userName: 'public',
    password: 'public'
}
// topic to subscribe to when you connect:
var input_topic = 'input_topic_name';
// topic to publish:
var output_topic = 'output_topic_name';

var sendButton;  // button to send mqtt message

var inData;      // variable for incoming mqtt data
var sensorVal = 0;
var ledVal = 0;

function setup() {
    createCanvas(300, 300);
    // Create an MQTT client:
    client = new Paho.MQTT.Client(broker.hostname, Number(broker.port), creds.clientID);
    // set callback handlers for the client:
    client.onConnectionLost = onConnectionLost;
    client.onMessageArrived = onMessageArrived;
    // connect to the MQTT broker:
    client.connect(
      {
        onSuccess: onConnect,       // callback function for when you connect
        userName: creds.userName,   // username
        password: creds.password,   // password
        useSSL: true                // use SSL
      }
    );
    // create the send button:
    sendButton = createButton('toggle LED');
    sendButton.position(20, height-40);
    sendButton.mousePressed(sendMqttMessage);
}

function draw() {
  background(0);
  fill(255);
  text("sensor value: " + sensorVal, 20, 30);
  brightnessVal = map(sensorVal, 0, 4095, 0, 255)
  fill(brightnessVal);
  ellipse(width/2, height/2, 100, 100);
}

// called when the client connects
function onConnect() {
  print('client is connected');
  client.subscribe(input_topic);
}

// called when the client loses its connection
function onConnectionLost(response) {
  if (response.errorCode !== 0) {
    print('onConnectionLost:' + response.errorMessage);
  }
}

// function called when a message arrives:
function onMessageArrived(message) {
  var inData = message.payloadString;
  print('message received: ' + inData);
  sensorVal = parseInt(inData);
}

// functioned called to send a message:
function sendMqttMessage() {
  // if the client is connected to the MQTT broker:
  if (client.isConnected()) {
    if(ledVal == 0)
      ledVal = 1;
    else
      ledVal = 0;
    var msg = String(ledVal);
    // start an MQTT message:
    message = new Paho.MQTT.Message(msg);
    // choose the destination topic:
    message.destinationName = output_topic;
    client.send(message);
    print('message sent: ' + msg);
  }
}