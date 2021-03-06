#include <Arduino.h>
#include <FS.h>

#include "config.h"
#include "connection.h"
#include "webServer.h"

void setup() {
  Serial.begin(115200);

  SPIFFS.begin();

  WebServer.start();

  WifiConnection.start();
}

void loop() {
  if (WebServer.shouldRestartConnection) {
    WifiConnection.start();

    WebServer.shouldRestartConnection = false;
  }
}