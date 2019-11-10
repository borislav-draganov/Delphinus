#include <Arduino.h>
#include <FS.h>

#include "config.h"
#include "connectivity.h"
#include "webServer.h"

void setup() {
  Serial.begin(115200);

  SPIFFS.begin();

  initSensorConfig();

  startWebServer();

  startWiFiConnection();
}

void loop() {
}