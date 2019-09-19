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
  return (int)((value * factor) * 10.0f);
}

State SampleMode(const State_struct *currentState, unsigned long currentTime, MPU9250 *imu) {
  imu->readSensor();

  float magA = sqrt((imu->getAccelX_mss() * imu->getAccelX_mss()) +
                    (imu->getAccelY_mss() * imu->getAccelY_mss()) +
                    (imu->getAccelZ_mss() * imu->getAccelZ_mss()));

  float magR = sqrt((imu->getGyroX_rads() * imu->getGyroX_rads()) +
                    (imu->getGyroY_rads() * imu->getGyroY_rads()) +
                    (imu->getGyroZ_rads() * imu->getGyroZ_rads()));


  if (currentTime - currentState->lastDataSend > DATA_SEND_PERIOD) {
    // Send raw data to our server at a periodic interval.
    String url = String(SERVER_ADDR) + "dat?id="+SENSOR_ID+
                                       "&ax="+convert(imu->getAccelX_mss(), MSS_TO_GFORCE)+
                                       "&ay="+convert(imu->getAccelY_mss(), MSS_TO_GFORCE)+
                                       "&az="+convert(imu->getAccelZ_mss(), MSS_TO_GFORCE)+
                                       "&am="+convert(currentState->maxAccMag, MSS_TO_GFORCE)+
                                       "&gx="+convert(imu->getGyroX_rads(), RADS_TO_RPM)+
                                       "&gy="+convert(imu->getGyroY_rads(), RADS_TO_RPM)+
                                       "&gz="+convert(imu->getGyroZ_rads(), RADS_TO_RPM)+
                                       "&rm="+convert(currentState->maxRotMag, RADS_TO_RPM);

    return State{url,
                 currentState->steps,
                 currentState->lastStep,
                 currentTime,
                 0.0f,
                 0.0f,
                 &BroadcastMode};
  }

  if ((magA > STEP_THRESH) && ((currentTime - currentState->lastStep) > MIN_STEP_DURATION)) {
    //Step detected, inform the server.
    String url = String(SERVER_ADDR) + "step?id="+SENSOR_ID+
                                           "&s=" + (currentState->steps + 1);

    return State{url,
                 currentState->steps + 1,
                 currentTime,
                 currentState->lastDataSend,
                 max(magA, currentState->maxAccMag),
                 max(magR, currentState->maxRotMag),
                 &BroadcastMode};
  }

  return State{currentState->url,
               currentState->steps,
               currentState->lastStep,
               currentState->lastDataSend,
               max(magA, currentState->maxAccMag),
               max(magR, currentState->maxRotMag),
               currentState->update};
}

State BroadcastMode(const State_struct *currentState, unsigned long currentTime, MPU9250 *imu) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, currentState->url);
  http.GET();
  http.end();

  return State{"",
               currentState->steps,
               currentState->lastStep,
               currentState->lastDataSend,
               currentState->maxAccMag,
               currentState->maxRotMag,
               &SampleMode};
}
