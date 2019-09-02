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
#include <ESP8266HTTPClient.h>

#include "statum_ped.h"
#include "configuration.h"

int convert(float value, float factor) {
  return (int)((value * factor) * 100.0f);
}

State SampleMode(const State_struct *currentState, unsigned long currentTime, MPU9250 *imu) {
  imu->readSensor();

  float magA = sqrt((imu->getAccelX_mss() * imu->getAccelX_mss()) +
                    (imu->getAccelY_mss() * imu->getAccelY_mss()) +
                    (imu->getAccelZ_mss() * imu->getAccelZ_mss()));

  float magR = sqrt((imu->getGyroX_rads() * imu->getGyroX_rads()) +
                    (imu->getGyroY_rads() * imu->getGyroY_rads()) +
                    (imu->getGyroZ_rads() * imu->getGyroZ_rads()));

  // Send raw data to our server at a periodic interval.
  if (currentTime - currentState->lastDataSend > DATA_SEND_PERIOD) {
    State newState;

    newState.url = String(SERVER_ADDR) + "dat?id="+SENSOR_ID+
                                            "&ax="+convert(imu->getAccelX_mss(), MSS_TO_GFORCE)+
                                            "&ay="+convert(imu->getAccelY_mss(), MSS_TO_GFORCE)+
                                            "&az="+convert(imu->getAccelZ_mss(), MSS_TO_GFORCE)+
                                            "&am="+convert(magA, MSS_TO_GFORCE)+
                                            "&gx="+convert(imu->getGyroX_rads(), RADS_TO_RPM)+
                                            "&gy="+convert(imu->getGyroY_rads(), RADS_TO_RPM)+
                                            "&gz="+convert(imu->getGyroZ_rads(), RADS_TO_RPM)+
                                            "&rm="+convert(magR, RADS_TO_RPM);

    Serial.println(newState.url);
    newState.lastStep = currentState->lastStep;
    newState.lastDataSend = currentTime;
    newState.update = &BroadcastMode;

    return newState;
  }

  // OPTIONAL: enforce minimum time between steps.
  if (magA > STEP_THRESH) {
    //Sends step information to our server
    State newState;

    newState.steps = currentState->steps + 1;
    newState.url = String(SERVER_ADDR) + "step?s=" + newState.steps;
    newState.lastStep = currentTime;
    newState.lastDataSend = currentState->lastDataSend;
    newState.update = &BroadcastMode;

    return newState;
  }

  return *currentState;
}

State BroadcastMode(const State_struct *currentState, unsigned long currentTime, MPU9250 *imu) {
  // Sends raw data to our server every 500ms.
  WiFiClient client;
  HTTPClient http;

  http.begin(client, currentState->url);
  http.GET();
  http.end();

  State newState;
  newState.lastStep = currentState->lastStep;
  newState.lastDataSend = currentState->lastDataSend;
  newState.update = &SampleMode;

  return newState;
}
