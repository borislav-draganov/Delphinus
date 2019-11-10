#include <Arduino.h>
#include <FS.h>

#include "webServer.h"
#include "connectivity.h"

void setup() {
  Serial.begin(115200);

  SPIFFS.begin();

  initSensorConfig();

  startWebServer();

  startWiFiConnection();
}

void loop() {
}