#ifndef LEDS_H
#define LEDS_H

#include "Arduino.h"
#include "state.h"
#include "config.h"

#define PIN_LIGHT_0     32
#define PIN_LIGHT_1     33
#define PIN_LIGHT_2     25
#define PIN_LIGHT_3     26
#define PIN_PARROT_0    27
#define PIN_PARROT_1    14


//Driver for all internal LEDs called "Lights".
namespace Lights
{
    extern byte values[4];
    extern byte parrot_values[2];

    void begin();

    void _updateAll();

    void setValuesForActiveRooms(byte qls_value, byte ref_value);

    void turnOff();

}





#endif