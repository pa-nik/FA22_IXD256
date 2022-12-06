// Example of reading the MPU6050 Intertial Measurement Unit (IMU)
// with the M5Stack Core Ink Board

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "M5CoreInk.h" 

Adafruit_MPU6050 imu;

Ink_Sprite PageSprite(&M5.M5Ink);  // e-ink display sprite
unsigned long updateTimer = 0;

void setup(void) {
  M5.begin(); 
  // default uses bottom connector pins G32 (SDA), G33 (SCL)
  Wire.begin(21, 22); // use back connector pins G21 (SDA), G22 (SCL)
  Serial.begin(9600);
  
  // initialize imu:
  if (imu.begin()) { 
    imu.setAccelerometerRange(MPU6050_RANGE_8_G);
    imu.setGyroRange(MPU6050_RANGE_500_DEG);
    imu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }
  else {
    Serial.println("Failed to find MPU6050 chip");
  }
}

void loop() {

  if(millis() > updateTimer + 100) {

    // get new sensor events:
    sensors_event_t a, g, temp;
    imu.getEvent(&a, &g, &temp);

    // print accelerometer values to Serial:
    Serial.print(a.acceleration.x);
    Serial.print(", ");
    Serial.print(a.acceleration.y);
    Serial.print(", ");
    Serial.print(a.acceleration.z);
    Serial.print(", ");

    // print gyroscope values to Serial:
    Serial.print(g.gyro.x);
    Serial.print(", ");
    Serial.print(g.gyro.y);
    Serial.print(", ");
    Serial.print(g.gyro.z);
    Serial.println("");

    updateTimer = millis();
  }

  M5.update();
}