#include "config.h"

String wifiConfigFile = "/wifi.json";
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

    File configFile = SPIFFS.open(wifiConfigFile, "w");
    if (!configFile) {
        Serial.println("Error opening file for writing");
        return;
    }

    if (serializeJson(doc, configFile) == 0) {
        Serial.println("Failed to write to file");
    } else {
        Serial.println("Saved");
    }

    configFile.close();
}

String getSsid() {
    return ssid;
}

String getPassword() {
    return password;
}