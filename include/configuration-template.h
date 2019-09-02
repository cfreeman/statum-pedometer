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
#ifndef _CONFIGURATION_ACH_
#define _CONFIGURATION_ACH_

#define SSID "********"                       // EditThis: The name of your WiFi access point.
#define PASSWORD "**********"                 // EditThis: The password of your WiFi access point.
#define SERVER_ADDR "**********************"  // EditThis: The destination server for sensor data.
#define SENSOR_ID "A"						  // EditThis: The identifier to use when notifying the server of the data source.
#define DATA_SEND_PERIOD 500                  // EditThis: The period in milliseconds to send data to the server.
#define STEP_THRESH 1.1f                      // EditThis: The threshold in m/s^2 that triggers a step to be detected.
#define MIN_STEP_DURATION 240				  // EditThis: The minimum time a step can take in milliseconds. 240ms -> 250 steps per minute.
#define DECLINATION_ANGLE -0.11               // EditThis: The declination angle for your current location.
                                              //           Find yours here: http://www.magnetic-declination.com/

#define MSS_TO_GFORCE 0.1020408163
#define RADS_TO_RPM 9.5492965855

#endif