#include "config.h"

String wifiConfigFile = "/wifi.json";
String ssid;
String password;

bool readWiFiConfig() {
    Serial.println("Reading WiFi Config");

    if (SPIFFS.exists(wifiConfigFile)) {
        Serial.println("WiFi Config file exists");
        File config = SPIFFS.open(wifiConfigFile, "r");

        DynamicJsonDocument doc(1024);
        
        DeserializationError error = deserializeJson(doc, config.readString());
        if (error) {
            Serial.print("Error parsing JSON: ");
            Serial.println(error.c_str());

            return false;
        }

        ssid = doc["ssid"].as<String>();
        password = doc["password"].as<String>();

        return true;
    } else {
        return false;
    }
}

String getSsid() {
    return ssid;
}

String getPassword() {
    return password;
}