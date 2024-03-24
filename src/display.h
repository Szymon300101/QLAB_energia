#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>
#include "utils/blinker.h"

#define DISPLAY_BRIGHTNESS 0x0f

#define STATUS_LED_PIN_A1 1
#define STATUS_LED_PIN_A2 3
#define STATUS_LED_PIN_B1 16
#define STATUS_LED_PIN_B2 17

namespace Display
{
    extern TM1637Display display_A;
    extern TM1637Display display_B;

    void begin();
    void displayErrorCode(byte code);
}

#endif