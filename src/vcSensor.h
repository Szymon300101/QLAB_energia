#ifndef VC_H
#define VC_H

#include <Wire.h>
#include <Adafruit_INA219.h>    //included locally, because of modified Adafruit_INA219.cpp file.

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


    VcSensor(byte i2c_addr) : ina219(i2c_addr)
    {
        _i2c_addr = i2c_addr;
    }

    bool begin()
    {
        // Initialize the INA219.
        // By default the initialization will use the largest range (32V, 2A).  However
        // you can call a setCalibration function to change this range (see comments).
        if (! ina219.begin()) {
            Serial.print("ERROR: Failed to find INA219 with address: ");
            Serial.println(_i2c_addr);
            return false;
        }
        //ina219.setCalibration_32V_1A();
        //ina219.setCalibration_16V_400mA();

        return true;
    }

    void read()
    {
        shuntvoltage_mV = ina219.getShuntVoltage_mV();
        busvoltage_V = ina219.getBusVoltage_V();
        current_mA = ina219.getCurrent_mA();
        power_mW = ina219.getPower_mW();
        loadvoltage_V = busvoltage_V + (shuntvoltage_mV / 1000);
    }
};



#endif