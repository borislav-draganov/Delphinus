#include "config.h"

const String wifiConfigFile     = "/wifi.json";
const String sensorConfigFile   = "/sensors.json";

const String defaultRedSensorName       = "Red";
const String defaultYellowSensorName    = "Yellow";
const String defaultBlueSensorName      = "Blue";
const String defaultGreenSensorName     = "Green";
const int defaultUpdateInterval         = 300000;

String ssid;
String password;

bool loadWiFiConfig() {
    Serial.println("Reading WiFi Config");

    if (SPIFFS.exists(wifiConfigFile)) {
        Serial.println("WiFi Config file exists");
        File configFile = SPIFFS.open(wifiConfigFile, "r");

        StaticJsonDocument<128> doc;
        
        DeserializationError error = deserializeJson(doc, configFile.readString());
        configFile.close();
        
        if (error) {
            Serial.print("Error parsing JSON: ");
            Serial.println(error.c_str());

            return false;
        }

        ssid = doc["ssid"].as<String>();
        password = doc["password"].as<String>();

        return true;
    } else {
        Serial.println("WiFi Config file doesn't exist");

        return false;
    }
}

void saveWifiConfig(String ssid, String password) {
    StaticJsonDocument<128> doc;
    doc["ssid"] = ssid;
    doc["password"] = password;

    saveJsonToConFigFile(wifiConfigFile, doc);
}

void initSensorConfig() {
    if (!SPIFFS.exists(sensorConfigFile)) {
        Serial.println("Init default sensor config");

        StaticJsonDocument<128> doc;
        doc["redSensorName"] = defaultRedSensorName;
        doc["yellowSensorName"] = defaultYellowSensorName;
        doc["blueSensorName"] = defaultBlueSensorName;
        doc["greenSensorName"] = defaultGreenSensorName;
        doc["updateInterval"] = defaultUpdateInterval;

        saveJsonToConFigFile(sensorConfigFile, doc);
    } else {
        Serial.println("Sensor config already set");
    }
}

void saveSensorConfig(String redSensorName, String yellowSensorName, String blueSensorName, String greenSensorName, int updateInterval) {
    StaticJsonDocument<128> doc;
    doc["redSensorName"] = redSensorName;
    doc["yellowSensorName"] = yellowSensorName;
    doc["blueSensorName"] = blueSensorName;
    doc["greenSensorName"] = greenSensorName;
    doc["updateInterval"] = updateInterval;

    saveJsonToConFigFile(sensorConfigFile, doc);
}

bool saveJsonToConFigFile(String fileName, StaticJsonDocument<128> doc) {
    File configFile = SPIFFS.open(fileName, "w");
    if (!configFile) {
        Serial.println("Error opening file for writing");
        return false;
    }

    if (serializeJson(doc, configFile) == 0) {
        Serial.println("Failed to write to file");
        return false;
    } else {
        Serial.println("Saved");
    }

    configFile.close();
    return true;
}

String getSsid() {
    return ssid;
}

String getPassword() {
    return password;
}