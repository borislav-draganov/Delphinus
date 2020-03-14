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
        static OneWire oneWireRedSensor;
        static OneWire oneWireYellowSensor;
        static OneWire oneWireBlueSensor;
        static OneWire oneWireGreenSensor;

        static DallasTemperature redSensor;
        static DallasTemperature yellowSensor;
        static DallasTemperature blueSensor;
        static DallasTemperature greenSensor;

        StaticJsonDocument<128> getAllTemperaturesAsJson();

        float getTemperature(DallasTemperature sensor);
        float getRedSensorTemperature();
        float getYellowSensorTemperature();
        float getBlueSensorTemperature();
        float getGreenSensorTemperature();
};

extern DallasSensors Dallas;

#endif