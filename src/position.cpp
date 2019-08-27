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
#include "position.h"
#include "configuration.h"

float heading(MPU9250 *mpu) {
  float xMag = mpu->getMagX_uT();
  float yMag = mpu->getMagY_uT();

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(xMag, yMag);

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  heading = heading + DECLINATION_ANGLE;

  // Correct for when signs are reversed.
  if (heading < 0) {
    heading += 2*PI;
  }

  // Check for wrap due to addition of declination.
  if (heading > 2*PI) {
    heading -= 2*PI;
  }

  // Convert radians to degrees for readability.
  return heading * 180/M_PI;



  // if (xMax == 0.0) {
  //   xMax = event.magnetic.x;
  // }

  // if (yMax == 0.0) {
  //   yMax = event.magnetic.y;
  // }

  // if (calibrate) {
  //   xMax = max(xMax, event.magnetic.x);
  //   yMax = max(yMax, event.magnetic.y);
  //   xMin = min(xMin, event.magnetic.x);
  //   yMin = min(yMin, event.magnetic.y);
  // }

  // // Serial.print("xMax: "); Serial.print(xMax); Serial.print(" ");
  // // Serial.print("xMin: "); Serial.print(xMin); Serial.print(" ");
  // // Serial.print("yMax: "); Serial.print(yMax); Serial.print(" ");
  // // Serial.print("yMin: "); Serial.print(yMin); Serial.println(" ");
  // //delay(500);

  // // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // // Calculate heading when the magnetometer is level, then correct for signs of axis.
  // float heading = atan2((event.magnetic.y - ((yMax + yMin) / 2.0)), (event.magnetic.x - ((xMax + xMin) / 2.0)));

  // //Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  // //Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  // //Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  // // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // // Find yours here: http://www.magnetic-declination.com/
  // // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  // float declinationAngle = -0.11; // Cairns magnetic declination.
  // //float declinationAngle = 0.22;
  // heading += declinationAngle;

  // // Correct for when signs are reversed.
  // if (heading < 0) {
  //   heading += 2*PI;
  // }

  // // Check for wrap due to addition of declination.
  // if (heading > 2*PI) {
  //   heading -= 2*PI;
  // }

  // // Convert radians to degrees for readability.
  // float headingDegrees = heading * 180/M_PI;

  //return 0.0f;
}