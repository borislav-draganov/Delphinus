#include "connectivity.h"

const char* apSsid = "Delphinus";
const char* apPassword = "123456789";

IPAddress localIp(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void startWiFiConnection() {
    startAsAccessPoint();
}

void startAsAccessPoint() {
    WiFi.mode(WIFI_AP);

    Serial.print("Setting soft-AP configuration... ");
    Serial.println(WiFi.softAPConfig(localIp, gateway, subnet) ? "Ready" : "Failed!");
    
    Serial.print("Setting soft-AP... ");
    Serial.println(WiFi.softAP(apSsid, apPassword) ? "Ready" : "Failed!");
}