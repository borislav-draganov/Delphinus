#include "dallas.h"

#include <OneWire.h>

OneWire oneWireRedSensor(RED_SENSOR);
DallasTemperature dsRedSensor(&oneWireRedSensor);

OneWire oneWireYellowSensor(YELLOW_SENSOR);
DallasTemperature dsYellowSensor(&oneWireYellowSensor);

OneWire oneWireBlueSensor(BLUE_SENSOR);
DallasTemperature dsBlueSensor(&oneWireBlueSensor);

OneWire oneWireGreenSensor(GREEN_SENSOR);
DallasTemperature dsGreenSensor(&oneWireGreenSensor);

StaticJsonDocument<128> DallasSensors::getAllTemperaturesAsJson() {
  StaticJsonDocument<128> doc;
  doc["redSensor"] = getTemperature(dsRedSensor);
  doc["yellowSensor"] = getTemperature(dsYellowSensor);
  doc["blueSensor"] = getTemperature(dsBlueSensor);
  doc["greenSensor"] = getTemperature(dsGreenSensor);

  return doc;
}

float DallasSensors::getTemperature(DallasTemperature sensor) {
  sensor.requestTemperatures();

  return sensor.getTempCByIndex(0);
}

DallasSensors Dallas;