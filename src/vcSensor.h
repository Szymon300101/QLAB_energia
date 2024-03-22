#ifndef VC_H
#define VC_H

#include <Wire.h>
#include <Adafruit_INA219.h>
#include "state.h"

class VcSensor
{
    byte _i2c_addr;
    Adafruit_INA219 ina219;

public:
    float shuntvoltage_mV = 0;
    float busvoltage_V = 0;
    float current_mA = 0;
    float loadvoltage_V = 0;
    float power_mW = 0;

    VcSensor(byte i2c_addr);

    bool begin();

    void read();
};

#endif
