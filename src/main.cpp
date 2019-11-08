#include <Arduino.h>

#include "connectivity.h"
#include "webServer.h"
#include "dallas.h"

void setup() {
  Serial.begin(115200);

  startWebServer();

  startWiFiConnection();
}

void loop() {
  // getTemperature();

  handleClient(); 

  // delay(5000);
}