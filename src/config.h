#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>

class Configuration {
    public:
       bool loadWiFiConfig();

       void saveWifiConfig(String ssid, String password);

       void initSensorConfig();

       void saveSensorConfig(String redSensorName, String yellowSensorName, String blueSensorName, String greenSensorName);

       String getSsid();

       String getPassword();

    private:
        bool saveJsonToConfigFile(String fileName, StaticJsonDocument<128> json);

        String wifiConfigFile             = "/wifi.json";
        String sensorConfigFile           = "/sensors.json";
        String defaultRedSensorName       = "Red";
        String defaultYellowSensorName    = "Yellow";
        String defaultBlueSensorName      = "Blue";
        String defaultGreenSensorName     = "Green";

        String ssid;
        String password;
};

extern Configuration Config;

#endif