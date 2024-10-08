#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>
#include "utils/blinker.h"
#include "state.h"
#include "sensors.h"

#define DISPLAY_BRIGHTNESS 5 // 0-7

#define STATUS_LED_PIN_A1 2
#define STATUS_LED_PIN_A2 15
#define STATUS_LED_PIN_B1 12
#define STATUS_LED_PIN_B2 0

//Driver for LED displays and status LEDs
namespace Display
{
    extern TM1637Display display_A;
    extern TM1637Display display_B;

    void begin();
    void displayState();
    void displayErrorCode(byte code);
    void clearLed();
}

#endif