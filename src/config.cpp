#include "config.h"

#include <FS.h>

bool Configuration::loadWiFiConfig() {
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

void Configuration::saveWifiConfig(String ssid, String password) {
    StaticJsonDocument<128> doc;
    doc["ssid"] = ssid;
    doc["password"] = password;

    saveJsonToConfigFile(wifiConfigFile, doc);
}

void Configuration::saveSensorConfig(String redSensorName, String yellowSensorName, String blueSensorName, String greenSensorName, String powerSensorName) {
    StaticJsonDocument<128> doc;
    doc["redSensorName"] = redSensorName;
    doc["yellowSensorName"] = yellowSensorName;
    doc["blueSensorName"] = blueSensorName;
    doc["greenSensorName"] = greenSensorName;
    doc["powerSensorName"] = powerSensorName;

    saveJsonToConfigFile(sensorConfigFile, doc);
}

bool Configuration::saveJsonToConfigFile(String fileName, StaticJsonDocument<128> doc) {
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

String Configuration::getSsid() {
    return ssid;
}

String Configuration::getPassword() {
    return password;
}

Configuration Config;