#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>
#include "utils/blinker.h"

#define DISPLAY_BRIGHTNESS 0x0f

#define STATUS_LED_PIN_A1 10
#define STATUS_LED_PIN_A2 11
#define STATUS_LED_PIN_B1 12
#define STATUS_LED_PIN_B2 13

namespace Display
{
    extern TM1637Display display_A;
    extern TM1637Display display_B;

    void begin();
    void displayErrorCode(byte code);
}

#endif