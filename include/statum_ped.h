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
#ifndef _STATUM_PED_ACH_
#define _STATUM_PED_ACH_

#include <MPU9250.h>

typedef struct State_struct (*StateFn)(const struct State_struct *currentState, unsigned long currentTime, MPU9250 *imu);

typedef struct State_struct {
  String url;

  unsigned long steps;
  unsigned long lastStep;
  unsigned long lastDataSend;

  float maxAccMag;
  float maxRotMag;

  StateFn update;
} State;

State SampleMode(const State_struct *currentState, unsigned long currentTime, MPU9250 *imu);
State BroadcastMode(const State_struct *currentState, unsigned long currentTime, MPU9250 *imu);


#endif