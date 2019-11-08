#include "connectivity.h"
#include "config.h"

String apSsid = "Delphinus";
String apPassword = "123456789";

IPAddress localIp(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void startWiFiConnection() {
    WiFi.softAPdisconnect();
    WiFi.disconnect();

    Serial.print("WiFi config loading...");
    bool isWiFiConfigSet = readWiFiConfig();

    if (isWiFiConfigSet) {
        attemptToConnect();
    } else {
        startAsAccessPoint();
    }
}

void attemptToConnect() {
    Serial.println("Starting in Station mode");
    
    String ssid = getSsid();
    String password = getPassword();
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(password);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");

        unsigned long now = millis();

        if ((now - startTime) >= 5000 || WiFi.status() == WL_CONNECTED) {
            break;
        }
    } 

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected");
    } else {
        startAsAccessPoint();
    }
}

void startAsAccessPoint() {
    Serial.println("Starting in AP mode");
    WiFi.mode(WIFI_AP);

    Serial.print("Setting soft-AP configuration... ");
    Serial.println(WiFi.softAPConfig(localIp, gateway, subnet) ? "Ready" : "Failed!");

    WiFi.hostname(apSsid);

    Serial.print("Setting soft-AP... ");
    Serial.println(WiFi.softAP(apSsid, apPassword) ? "Ready" : "Failed!");

    MDNS.begin(apSsid);
    MDNS.addService("http", "tcp", 80);
}