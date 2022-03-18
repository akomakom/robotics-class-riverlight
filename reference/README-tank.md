2-motor tank code
-----


# Model

This code is applicable to the keyestudio mini tank robot V2
This device uses an Arduino UNO R3 and has:
* 2x light sensors (A1/A2)
* 1x IR receiver ()
* 1x Ultrasonic rangefinder (A4/A5)
* 1x rangefinder servo (9)

# Software Installation

## Arduino Libraries

Install using the Arduino IDE's Library Manager:
* Adafruit GFX
* TM16xx (Maxint)

Install by downloading a zip file and adding it in Arduino IDE
* IR Tank library from keyestudio: https://wiki.keyestudio.com/Ks0428_keyestudio_Mini_Tank_Robot_V

## Project Libraries

On Linux, it is possible to symlink tank-library to ~/Arduino/libraries/
On other platforms, it may be easier to copy.
