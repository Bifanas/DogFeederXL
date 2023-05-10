#include "HX711.h"

#define calibration_factor 104400 
#define system_weight -4.592
#define DOUT  3
#define CLK  2

HX711 scale;

float storage(){
  float aux = scale.get_units() - system_weight;
  return aux;
}
void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); 
}

void loop() {

  Serial.print(storage());
  Serial.print(" kg");
  Serial.println();
  delay(1000);
}