#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>

class LedDisplay
{
    byte _clk;
    byte _dio;
    TM1637Display _display;

public:
    LedDisplay(byte clk, byte dio) : _display(clk, dio)
    {
        _clk = clk;
        _dio = dio;
    }

    void begin()
    {
        _display.setBrightness(0x0f);
    }

};



#endif