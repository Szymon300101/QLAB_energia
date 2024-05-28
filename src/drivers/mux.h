#ifndef MUX_H
#define MUX_H

#include <Arduino.h>
#include <Wire.h>

#define MUX_I2C_ADDR 0x70

namespace Mux
{
    void select(byte i);
}


#endif