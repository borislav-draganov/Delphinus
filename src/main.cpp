#include <Arduino.h>

#include "webServer.h"
#include "connectivity.h"

void setup() {
  Serial.begin(115200);

  startWebServer();

  startWiFiConnection();
}

void loop() {
  handleClient(); 
}