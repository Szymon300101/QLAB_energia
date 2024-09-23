#ifndef LEDS_H
#define LEDS_H

#include "Arduino.h"
#include "state.h"


#define LIGHT_NUM 4
#define PARROT_NUM 4

#define PIN_LIGHT_0     32
#define PIN_LIGHT_1     33
#define PIN_LIGHT_2     25
#define PIN_LIGHT_3     26
#define PIN_PARROT_0    27
#define PIN_PARROT_1    14

#define PARROT_VALUE 80

namespace Lights
{
    extern byte values[LIGHT_NUM];
    extern byte parrot_values[PARROT_NUM];

    void begin();

    void _updateAll();

    void setValuesForActiveRooms(byte qls_value, byte ref_value);



}





#endif