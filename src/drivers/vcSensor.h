#ifndef VC_H
#define VC_H

#include<Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

//Driver for Voltage/Current Sensor
class VcSensor
{
    byte _i2c_addr;
    Adafruit_INA219 ina219;

    float shuntvoltage_mV;
    float busvoltage_V;

public:
    float current_mA = 0;
    float loadvoltage_V = 0;
    float power_mW = 0;

    VcSensor(byte i2c_addr);

    bool begin();

    void read();
};

#endif
