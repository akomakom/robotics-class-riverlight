#ifndef TANK_MATRIX_H
#define TANK_MATRIX_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <TM1640.h>
#include <TM16xxMatrixGFX.h>

#define MODULE_SIZECOLUMNS 16    // number of GRD lines, will be the y-height of the display
#define MODULE_SIZEROWS 8    // number of SEG lines, will be the x-width of the display

#define VOLTAGE_CONVERSION_FACTOR 2 // for voltage divider (2 for equal resistor divider, eg 2*3K)

#define TEXT_SCROLL_WAIT 50
#define TEXT_SPACER 1
#define TEXT_WIDTH 5+TEXT_SPACER

class Tank_Matrix : public TM16xxMatrixGFX {
  public:
    Tank_Matrix(byte dataPin, byte clockPin, int voltagePin, int cellCount = 2);
    void display(String text);
    void drawMeter(int value, int min, int max, int positionPercent = 100, int width = 1);
    void drawVoltageMeter();
    float getVoltage();
  private:
    void drawText(String tape);
    void scrollText(String tape);
  
    int _voltagePin; // resistor voltage divider connected to analog pin 3
    float _voltageTotal;
    float _voltagePerCell;
    float _cellCount;

    TM1640* _module;
    TM16xxMatrixGFX* _matrix;
};
#endif
