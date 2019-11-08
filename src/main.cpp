#include <Arduino.h>
#include "dallas.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  getTemperature();

  delay(5000);
}