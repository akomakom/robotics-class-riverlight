/*
 * TM16xxMatrixGFX_Ticker
 * 
 * Arduino example sketch to demonstrate the Adafruit GFX library on a TM16xx driven LED Matrix
 * 
 * Based on Ticker.pde example of the MAX72xxPanel library
 * 
 * Confirmed to work in the following environments:
 *     - WeMos D1-mini and TM1640 8x8 MatrixLED Shield using Arduino IDE 1.6.10: DIN=D7/13/MOSI, CLK=D5/14/SCK, 253.516 bytes flash, 32.372 bytes RAM
 * 
 * For more information see  https://github.com/maxint-rd/TM16xx
 */

#include <Adafruit_GFX.h>
#include <TM1640.h>
#include <TM16xxMatrixGFX.h>

//TM1640 module(9, 10);    // DIN=9, CLK=10
TM1640 module(A4, A5);    // For ESP8266/WeMos D1-mini: DIN=D7/13/MOSI, CLK=D5/14/SCK
#define MODULE_SIZECOLUMNS 16    // number of GRD lines, will be the y-height of the display
#define MODULE_SIZEROWS 8    // number of SEG lines, will be the x-width of the display
TM16xxMatrixGFX matrix(&module, MODULE_SIZECOLUMNS, MODULE_SIZEROWS);    // TM16xx object, columns, rows

String tape = "Akom Was Here";
int wait = 100; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels


//voltage

int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read
float voltageTotal = 0;
float voltagePerCell = 0;
float voltageFactor = 1.9; // voltage divider is 1/2, with some inaccuracy
float cellCount = 2;



void setup()
{
  Serial.begin(9600);           //  setup serial
  
  matrix.setIntensity(2); // Use a value between 0 and 7 for brightness
  matrix.setRotation(1);
  matrix.setMirror(true);   // set X-mirror true when using the WeMOS D1 mini Matrix LED Shield (X0=Seg1/R1, Y0=GRD1/C1)
}

void loop()
{
//  scrollText(tape);
//  drawText("Hi there");
//  delay(1000);
//  drawText("You");
  scrollText(String(getVoltage(), 3));
  drawMeter(getVoltage() * 10, 34, 42); //voltage*10 (3.4v - 4.2v range)
  delay(1000);
}

float getVoltage() {
  val = analogRead(analogPin);  // read the input pin
  voltageTotal = val/1024.0*5.0*voltageFactor;
  voltagePerCell = voltageTotal / cellCount;
  return voltagePerCell;
}

void drawMeter(int value, int min, int max) {
  int adjustedValue = map(value, min, max, 0, matrix.height() - 1);
  for (int i = 0 ; i < matrix.height(); i++) {
    matrix.drawPixel(15, matrix.height() - i - 1, i > adjustedValue ? LOW : HIGH);
  }
  matrix.write();
}

void drawText(String tape) {
  matrix.fillScreen(LOW);
  for (int i = 0 ; i < matrix.width() && i < tape.length() ; i++ ) {
    matrix.drawChar(i * 5, 0, tape[i], HIGH, LOW, 1);
  }
  matrix.write(); // Send bitmap to display

}

void scrollText(String tape) {
  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        Serial.print("Drawing letter ");
        Serial.print(tape[letter]);
        Serial.print(" x/y: ");
        Serial.print(x);
        Serial.print("/");
        Serial.println(y);
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }
    matrix.write(); // Send bitmap to display
    delay(wait);
  }
}
