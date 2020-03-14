#include "dallas.h"

#include <OneWire.h>

OneWire DallasSensors::oneWireRedSensor(RED_SENSOR);
DallasTemperature DallasSensors::redSensor(&oneWireRedSensor);

OneWire DallasSensors::oneWireYellowSensor(YELLOW_SENSOR);
DallasTemperature DallasSensors::yellowSensor(&oneWireYellowSensor);

OneWire DallasSensors::oneWireBlueSensor(BLUE_SENSOR);
DallasTemperature DallasSensors::blueSensor(&oneWireBlueSensor);

OneWire DallasSensors::oneWireGreenSensor(GREEN_SENSOR);
DallasTemperature DallasSensors::greenSensor(&oneWireGreenSensor);

StaticJsonDocument<128> DallasSensors::getAllTemperaturesAsJson() {
  StaticJsonDocument<128> doc;
  doc["redSensor"] = getTemperature(redSensor);
  doc["yellowSensor"] = getTemperature(yellowSensor);
  doc["blueSensor"] = getTemperature(blueSensor);
  doc["greenSensor"] = getTemperature(greenSensor);

  return doc;
}

float DallasSensors::getTemperature(DallasTemperature sensor) {
  sensor.requestTemperatures();

  float temp = sensor.getTempCByIndex(0);

  return (temp * 100.0) / 100.0;
}

float DallasSensors::getRedSensorTemperature() {
  return getTemperature(redSensor);
}

float DallasSensors::getYellowSensorTemperature() {
  return getTemperature(yellowSensor);
}

float DallasSensors::getBlueSensorTemperature() {
  return getTemperature(blueSensor);
}

float DallasSensors::getGreenSensorTemperature() {
  return getTemperature(greenSensor);
}


DallasSensors Dallas;