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

// SPARKFUN LIB HAS PEDOMETER INSIDE

//MPU9250 IMU(Wire,0x68);

void setup() {
	Serial.begin(9600);
	Wire.begin();

	  // start communication with IMU
  // int status = IMU.begin();
  // if (status < 0) {
  //   Serial.println("IMU initialization unsuccessful");
  //   Serial.println("Check IMU wiring or try cycling power");
  //   Serial.print("Status: ");
  //   Serial.println(status);
  //   while(1) {}
  // }
  // // setting the accelerometer full scale range to +/-8G
  // IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // // setting the gyroscope full scale range to +/-500 deg/s
  // IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // // setting DLPF bandwidth to 20 Hz
  // IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // // setting SRD to 19 for a 50 Hz update rate
  // IMU.setSrd(19);
}



void loop() {
	int heartRate = 60;  // Default the heart rate to a fairly average resting rate.
  	int b = Wire.requestFrom(0xA0 >> 1, 1);
  	if (b > 0) {
    	heartRate = (int) Wire.read();
  	}

  	Serial.print("HR: ");
  	Serial.println(heartRate);

  // IMU.readSensor();

  // // display the data
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

  	delay(500);
}