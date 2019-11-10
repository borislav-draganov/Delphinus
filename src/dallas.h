#include <ArduinoJson.h>
#include <DallasTemperature.h>

#define RED_SENSOR D3
#define YELLOW_SENSOR D4
#define BLUE_SENSOR D5
#define GREEN_SENSOR D6

StaticJsonDocument<128> getAllTemperaturesAsJson();

float getTemperature(DallasTemperature sensor);