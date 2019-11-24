#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>

bool loadWiFiConfig();

void saveWifiConfig(String ssid, String password);

void initSensorConfig();

void saveSensorConfig(String redSensorName, String yellowSensorName, String blueSensorName, String greenSensorName);

bool saveJsonToConfigFile(String fileName, StaticJsonDocument<128> json);

String getSsid();

String getPassword();

#endif