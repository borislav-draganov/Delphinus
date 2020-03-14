#ifndef SENSORS_H
#define SENSORS_H

#include <ArduinoJson.h>

class SensorsHub {
    public:
        float getPowerSensorReading();

        StaticJsonDocument<128> getAllSensorDataAsJSON();
};

extern SensorsHub Sensors;

#endif