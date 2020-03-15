#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>

class Configuration {
    public:
       bool loadWiFiConfig();

       void saveWifiConfig(String ssid, String password);

       void saveSensorConfig(String redSensorName, String yellowSensorName, String blueSensorName, String greenSensorName, String powerSensorName);

       String getSsid();

       String getPassword();

    private:
        String wifiConfigFile             = "/wifi.json";
        String sensorConfigFile           = "/sensors.json";

        String ssid;
        String password;

        bool saveJsonToConfigFile(String fileName, StaticJsonDocument<128> json);
};

extern Configuration Config;

#endif