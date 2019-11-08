#include <Arduino.h>

#include "connectivity.h"
#include "dallas.h"

void setup() {
  Serial.begin(115200);

  startWiFiConnection();
}

void loop() {
  // getTemperature();

  delay(5000);
}