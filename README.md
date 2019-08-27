# Statum Pedometer

Software that powers a theatrical-grade pedometer. It transmits raw data from a
motion processing unit to audio visual computers, and can be used to trigger lighting
cues one a single step.


## Compiling:

1. Install [PlatformIO](https://docs.platformio.org/en/latest/installation.html).
2. Download or git clone CloudOLight source code.
3. Open a terminal and navigate to the source code location.
4. Copy the config template `$cp configuration-template.h configuration.h`
5. Edit the configuration.h as necessary.
6. Build the project: `$platformio run --target upload`


## Hardware Notes:
Power:
D1: 200mA
Accel Sensor: 1mA

Heart Rate: 10mA


## License

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
