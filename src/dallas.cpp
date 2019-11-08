#include "dallas.h"

OneWire oneWireFirstSensor(FIRST_SENSOR);
DallasTemperature dsFirstSensor(&oneWireFirstSensor);

void getTemperature() {
  dsFirstSensor.requestTemperatures();

  Serial.println(dsFirstSensor.getTempCByIndex(0));
}