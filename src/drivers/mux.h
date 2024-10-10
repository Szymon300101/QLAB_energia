#ifndef MUX_H
#define MUX_H

#include <Arduino.h>
#include <Wire.h>

#define MUX_I2C_ADDR 0x70

//Driver for I2C multiplexer
namespace Mux
{
    //select output as active (0-7)
    //WARNING: needs already initialised i2c bus
    void select(byte i); 
}


#endif