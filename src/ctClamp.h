#ifndef CT_CLAMP_H
#define CT_CLAMP_H

#include "EmonLib.h"

class CTClampSensor {
    public:
        CTClampSensor();

        double getApparentPower();
    private:
        EnergyMonitor emon;
};

extern CTClampSensor CTClamp;

#endif