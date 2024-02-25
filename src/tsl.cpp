#ifndef TSL_CPP
#define TSL_CPP

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include "mux.cpp"

#define INTEGR_TIME TSL2561_INTEGRATIONTIME_101MS

class Tsl
{
    byte _i2c_adrr;
    byte _mux_addr;
    
    Adafruit_TSL2561_Unified _sensor;

public:
    float val_lux;

    Tsl(byte mux_addr, byte i2c_adrr) : _sensor(i2c_adrr, -1)
    {
        _mux_addr = mux_addr;
        _i2c_adrr = i2c_adrr;
    }

    bool begin()
    {
        if(!_sensor.begin())
        {
            Serial.print("ERROR: TSL at addr: ");
            Serial.print(_mux_addr);
            Serial.print("/");
            Serial.print(_i2c_adrr, HEX);
            Serial.println(" not detected!");
            return false;
        }
        _sensor.enableAutoRange(false);
        _sensor.setIntegrationTime(INTEGR_TIME);

        return true;
    }

    //returns -1 on sensor overload
    float read_lux()
    {
        sensors_event_t event;

        Mux::select(_mux_addr);
        _sensor.getEvent(&event);
        
        if (event.light)
            val_lux = event.light;
        else
            val_lux = -1;

        return val_lux;
    }
};



#endif