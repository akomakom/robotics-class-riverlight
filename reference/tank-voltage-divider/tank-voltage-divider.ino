
// two equal resistor divider connected to analog pin 3
// outside leads to ground and Vbat
// cuts 2 lipo cell voltage in half to <5V so arduino can handle it
#define VOLTAGE_PIN A3

#define VOLTAGE_CONVERSION_FACTOR 2.0 // voltage divider is 1/2, with some inaccuracy
#define VOLTAGE_CELL_COUNT 2    // number of batteries in series

void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  int val = analogRead(VOLTAGE_PIN);  // read the input pin
  float voltageTotal = val/1024.0*5.0*VOLTAGE_CONVERSION_FACTOR;
  float voltagePerCell = voltageTotal / VOLTAGE_CELL_COUNT;

  Serial.print(val);          // debug value
  Serial.print(" -> ");
  Serial.print(voltagePerCell);
  Serial.print(" -> ");
  Serial.println(voltageTotal);

  delay(500);
}
