#include "tank_matrix.h"

/*
   Tank Library conveniences for using the matrix display board.
*/

Tank_Matrix::Tank_Matrix(byte dataPin, byte clockPin, int voltagePin, int cellCount) : TM16xxMatrixGFX(new TM1640(dataPin, clockPin), MODULE_SIZECOLUMNS, MODULE_SIZEROWS) {
  Serial.begin(9600);           //  setup serial in case we debug

//  _module = new TM1640(dataPin, clockPin);
//  _matrix = new TM16xxMatrixGFX(_module, MODULE_SIZECOLUMNS, MODULE_SIZEROWS);    // TM16xx object, columns, rows
  
  _voltageTotal = 0;
  _voltagePerCell = 0;
  _voltagePin = voltagePin;
  _cellCount = cellCount;

  setIntensity(2); // Use a value between 0 and 7 for brightness
  setRotation(1);
  setMirror(true);   // set X-mirror true when using the WeMOS D1 mini Matrix LED Shield (X0=Seg1/R1, Y0=GRD1/C1)

  Serial.println("Matrix initialized");
  display(String(getVoltage(), 1) + "v");
}

void Tank_Matrix::display(String tape) {
  if (tape.length() > (width() / TEXT_WIDTH)) {
    scrollText(tape);
  } else {
    drawText(tape);
  }
  drawVoltageMeter();
}


float Tank_Matrix::getVoltage() {
//  Serial.println("Reading voltage from pin " + String(_voltagePin));
  int val = analogRead(_voltagePin);  // read the input pin
  _voltageTotal =   val / 1024.0 * 5.0 * VOLTAGE_CONVERSION_FACTOR;
  _voltagePerCell = _voltageTotal / _cellCount;
  return _voltagePerCell;
}


void Tank_Matrix::drawVoltageMeter() {
  drawMeter(getVoltage() * 10, 34, 40); //voltage*10 (3.4v - 4.0v range for the bar)
}

/**
   Draw a vertical bar starting at the bottom,
   showing the value given on a scale from min to max
   X Position defaults to right-most
   
   value: number to graph
   min: minimum for the graph scale
   max: maximum for the graph scale
   positionPercent defaults to 100 (1-100 mapped to the width of the matrix).
   width: defaults to 1 pixel but can be wider.
*/
void Tank_Matrix::drawMeter(int value, int min, int max, int positionPercent, int meterWidth) {
  int adjustedValue = map(value, min, max, 0, height() - 1);
  int xPosition = map(positionPercent, 0, 100, 0, width() - 1);
//  Serial.print("Drawing a meter with value ");
//  Serial.print(adjustedValue);
//  Serial.print(" and x=");
//  Serial.println(xPosition);
  for (int i = 0 ; i < height(); i++) {
    // inner loop supports meter width > 1
    for (int j = 0 ; j < meterWidth ; j++) { 
      drawPixel(xPosition + j, height() - i - 1, i > adjustedValue ? LOW : HIGH);
    }
  }
  write();
}

/**
   Non-scrolling version (can print only a couple of characters)
*/
void Tank_Matrix::drawText(String tape) {
  fillScreen(LOW);
  int margin = max(0, (width() - (tape.length() * TEXT_WIDTH)) / 2); // try to center
  int y = (height() - 8) / 2; // center the text vertically
  for (int i = 0 ; i < width() && i < tape.length() ; i++ ) {
    drawChar((i * TEXT_WIDTH) + margin, y, tape[i], HIGH, LOW, 1);
  }
  write(); // Send bitmap to display

}



/**
   Scroll the given text once, starting off-screen.
*/
void Tank_Matrix::scrollText(String tape) {
  for ( int i = 0 ; i < TEXT_WIDTH * tape.length() + width() - 1 - TEXT_SPACER; i++ ) {
    fillScreen(LOW);

    int letter = i / TEXT_WIDTH;
    int x = (width() - 1) - i % TEXT_WIDTH;
    int y = (height() - 8) / 2; // center the text vertically

    while ( x + TEXT_WIDTH - TEXT_SPACER >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
//                Serial.print("Drawing letter ");
//                Serial.print(tape[letter]);
//                Serial.print(" i/x/y: ");
//                Serial.print(i);
//                Serial.print("/");
//                Serial.print(x);
//                Serial.print("/");
//                Serial.println(y);
        drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= TEXT_WIDTH;
    }
    write(); // Send bitmap to display
    delay(TEXT_SCROLL_WAIT);
  }
}
