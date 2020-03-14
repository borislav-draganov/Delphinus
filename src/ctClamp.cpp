#include "ctClamp.h"

#include "EmonLib.h"

CTClampSensor::CTClampSensor() {
    emon = EnergyMonitor();

    emon.current(A0, 0.047);
}

double CTClampSensor::getApparentPower() {
    double Irms = emon.calcIrms(1480);
  
    return Irms * 230.0;
}

CTClampSensor CTClamp;