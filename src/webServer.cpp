#include "webServer.h"

#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>

#include "config.h"
#include "connection.h"
#include "sensors.h"

AsyncWebServer server(80);

void RestWebServer::start() {
    Serial.println("Starting web server");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("GET /");

        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/bundle.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("GET /bundle.js");

        AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/bundle.js.gz", "application/javascript");
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("GET /favicon.ico");

        AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/favicon.ico.gz", "image/x-icon");
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("GET /sensors");

        StaticJsonDocument<128> doc = Sensors.getAllSensorDataAsJSON();

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        serializeJson(doc, *response);

        request->send(response);
    });

    AsyncCallbackJsonWebHandler* wiFiConfigPostHandler = new AsyncCallbackJsonWebHandler("/config/wifi", [](AsyncWebServerRequest *request, JsonVariant &json) {
        Serial.println("POST /config/wifi");
        
        JsonObject jsonObj = json.as<JsonObject>();

        String ssid = jsonObj["ssid"].as<String>();
        String password = jsonObj["password"].as<String>();

        Config.saveWifiConfig(ssid, password);

        request->send(200, "application/json", "{\"status\" : \"ok\"}");

        WebServer.shouldRestartConnection = true;
    });

    server.on("/config/sensors", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("GET /config/sensors");

        request->send(SPIFFS, "/sensors.json", "application/json");
    });

    AsyncCallbackJsonWebHandler* sensorsConfigPostHandler = new AsyncCallbackJsonWebHandler("/config/sensors", [](AsyncWebServerRequest *request, JsonVariant &json) {
        Serial.println("POST /config/sensors");
        
        JsonObject jsonObj = json.as<JsonObject>();

        String redSensorName = jsonObj["redSensorName"].as<String>();
        String yellowSensorName = jsonObj["yellowSensorName"].as<String>();
        String blueSensorName = jsonObj["blueSensorName"].as<String>();
        String greenSensorName = jsonObj["greenSensorName"].as<String>();

        Config.saveSensorConfig(redSensorName, yellowSensorName, blueSensorName, greenSensorName);

        request->send(200, "application/json", "{\"status\" : \"ok\"}");
    });

    server.addHandler(wiFiConfigPostHandler);
    server.addHandler(sensorsConfigPostHandler);

    server.begin();
}

RestWebServer WebServer;