#include "lights.h"

namespace Lights
{
    byte values[LIGHT_NUM] = {0,0,0,0};
    byte parrot_values[PARROT_NUM] = {0,0};

    void begin()
    {
        pinMode(PIN_LIGHT_0, OUTPUT);
        pinMode(PIN_LIGHT_1, OUTPUT);
        pinMode(PIN_LIGHT_2, OUTPUT);
        pinMode(PIN_LIGHT_3, OUTPUT);
        pinMode(PIN_PARROT_0, OUTPUT);
        pinMode(PIN_PARROT_1, OUTPUT);

        _updateAll();
    }

    void setValuesForActiveRooms(byte qls_value, byte ref_value)
    {
        values[0] = 0;
        values[1] = 0;
        values[2] = 0;
        values[3] = 0;
        parrot_values[0] = 0;
        parrot_values[1] = 0;

        values[State::getQlsActiveRoom()] = qls_value;
        parrot_values[State::getQlsActiveRoom()] = PARROT_VALUE;

        values[State::getRefActiveRoom()] = ref_value;

        _updateAll();
    }

    void _updateAll()
    {
        analogWrite(PIN_LIGHT_0, values[0]);
        analogWrite(PIN_LIGHT_1, values[1]);
        analogWrite(PIN_LIGHT_2, values[2]);
        analogWrite(PIN_LIGHT_3, values[3]);
        analogWrite(PIN_PARROT_0, parrot_values[0]);
        analogWrite(PIN_PARROT_1, parrot_values[1]);
    }
}