#include <Arduino.h>
#include <FS.h>

#include "config.h"
#include "connection.h"
#include "webServer.h"

void setup() {
  Serial.begin(115200);

  SPIFFS.begin();

  Config.initSensorConfig();

  WebServer.start();

  WifiConnection.start();
}

void loop() {
}