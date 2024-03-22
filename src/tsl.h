#ifndef TSL_H
#define TSL_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include "mux.h"
#include "state.h"

#define INTEGR_TIME TSL2561_INTEGRATIONTIME_101MS

class Tsl
{
    byte _i2c_adrr;
    byte _mux_addr;
    Adafruit_TSL2561_Unified _sensor;

public:
    float val_lux;

    Tsl(byte mux_addr, byte i2c_adrr);

    bool begin();

    float read_lux();
};

#endif
