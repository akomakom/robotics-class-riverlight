

int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read
float voltageTotal = 0;
float voltagePerCell = 0;
float factor = 1.9; // voltage divider is 1/2, with some inaccuracy
float cells = 2;


void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  val = analogRead(analogPin);  // read the input pin
  voltageTotal = val/1024.0*5.0*factor;
  voltagePerCell = voltageTotal / cells;
  Serial.print(val);          // debug value
  Serial.print(" -> ");
  Serial.print(voltagePerCell);
  Serial.print(" -> ");
  Serial.println(voltageTotal);
  delay(500);
}
