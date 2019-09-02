/*
 * Copyright (c) Clinton Freeman 2019
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <Arduino.h>
#include <Wire.h>
#include <MPU9250.h>

#include <ESP8266WiFi.h>

#include "position.h"
#include "statum_ped.h"
#include "configuration.h"

MPU9250 IMU(Wire, 0x68);

State state; // The current state of the statum pedometer.

void setup() {
	Serial.begin(9600);

	// Initialise the IMU.
  Serial.print("Initialising IMU...");
  Wire.begin();
  int status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_4G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
  Serial.println(" Done!");

  // Connect to WiFi.
  Serial.print("Connecting to Wifi");
  // Prevent need for powercyle after upload.
  WiFi.disconnect();

  // Use DHCP to connect and obtain IP Address.
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  // Wait until we have connected to the WiFi AP.
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }

  // // Init UDP to broadcast OSC messages.
  // Udp.begin(localPort);
  Serial.println(" Done!");

  // Initalise the state of the Statum pedometer.
  state.steps = 0;
  state.lastStep = millis();
  state.lastDataSend = state.lastStep;
  state.update = &SampleMode;
}


void loop() {
  state = state.update(&state, millis(), &IMU);
  Serial.println("loop");

  // TODO: Each sample call store the largest value to transmit.
  // TODO: Design Board.

  // display the data
  // Serial.print(IMU.getAccelX_mss(),6);
  // Serial.print("\t");
  // Serial.print(IMU.getAccelY_mss(),6);
  // Serial.print("\t");
  // Serial.print(IMU.getAccelZ_mss(),6);
  // Serial.print("\t");
  // Serial.print(IMU.getGyroX_rads(),6);
  // Serial.print("\t");
  // Serial.print(IMU.getGyroY_rads(),6);
  // Serial.print("\t");
  // Serial.print(IMU.getGyroZ_rads(),6);
  // Serial.print("\t");
  // Serial.print(IMU.getMagX_uT(),6);
  // Serial.print("\t");
  // Serial.print(IMU.getMagY_uT(),6);
  // Serial.print("\t");
  // Serial.print(IMU.getMagZ_uT(),6);
  // Serial.print("\t");
  // Serial.println(IMU.getTemperature_C(),6);

  delay(100);
}