#ifndef DALLAS_H
#define DALLAS_H

#include <ArduinoJson.h>
#include <DallasTemperature.h>

#define RED_SENSOR D3
#define YELLOW_SENSOR D4
#define BLUE_SENSOR D5
#define GREEN_SENSOR D6

class DallasSensors {
    public:
        StaticJsonDocument<128> getAllTemperaturesAsJson();

        float getTemperature(DallasTemperature sensor);
};

extern DallasSensors Dallas;

#endif