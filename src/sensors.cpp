#include "sensors.h"

#include "dallas.h"

StaticJsonDocument<128> SensorsHub::getAllSensorDataAsJSON() {
  StaticJsonDocument<128> doc;
  doc["redSensor"] = Dallas.getRedSensorTemperature();
  doc["yellowSensor"] = Dallas.getYellowSensorTemperature();
  doc["blueSensor"] = Dallas.getBlueSensorTemperature();
  doc["greenSensor"] = Dallas.getGreenSensorTemperature();
  doc["powerSensor"] = 0;

  return doc;
}

SensorsHub Sensors;