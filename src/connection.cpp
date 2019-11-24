#include "connection.h"

#include <ESP8266WiFi.h>

#include "config.h"

IPAddress localIp(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void Connection::start() {
    WiFi.softAPdisconnect();
    WiFi.disconnect();

    Serial.println("WiFi Config loading...");
    bool isWiFiConfigSet = Config.loadWiFiConfig();

    if (isWiFiConfigSet) {
        attemptToConnect();
    } else {
        startAsAccessPoint();
    }
}

void Connection::attemptToConnect() {
    Serial.println("Starting in Station mode");
    
    String ssid = Config.getSsid();
    String password = Config.getPassword();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");

        unsigned long now = millis();

        if ((now - startTime) >= 15000 || WiFi.status() == WL_CONNECTED) {
            break;
        }
    } 

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected");
    } else {
        startAsAccessPoint();
    }
}

void Connection::startAsAccessPoint() {
    Serial.println("Starting in AP mode");
    WiFi.mode(WIFI_AP);

    Serial.print("Setting soft-AP configuration... ");
    Serial.println(WiFi.softAPConfig(localIp, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP... ");
    Serial.println(WiFi.softAP(apSsid, apPassword) ? "Ready" : "Failed!");
}

Connection WifiConnection;