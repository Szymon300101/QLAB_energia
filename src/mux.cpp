#ifndef MUX_CPP
#define MUX_CPP

#include <Arduino.h>
#include <Wire.h>

#define MUX_I2C_ADDR 0x70

namespace Mux
{
    void select(byte i) {
        if (i > 7)
        {
            Serial.print("ERROR: Bad Mux addres: ");
            Serial.println(i);
            return;
        }
        
        Wire.beginTransmission(MUX_I2C_ADDR);
        Wire.write(1 << i);
        Wire.endTransmission();  
    }
}


#endif