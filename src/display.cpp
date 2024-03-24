#include "display.h"

namespace Display
{
    TM1637Display display_A = TM1637Display(2, 4); // CLK_PIN, DIO_PIN //TODO
    TM1637Display display_B = TM1637Display(0, 15); // CLK_PIN, DIO_PIN //TODO

    Blinker _error_blinker = Blinker(100, 2000);

    const uint8_t _error_segments[] = {
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, // E
        SEG_E | SEG_G,                         // r
        SEG_E | SEG_G                          // r
    };

    void begin()
    {
        display_A.setBrightness(DISPLAY_BRIGHTNESS);
        display_B.setBrightness(DISPLAY_BRIGHTNESS);

        pinMode(STATUS_LED_PIN_A1, OUTPUT);
        pinMode(STATUS_LED_PIN_A2, OUTPUT);
        pinMode(STATUS_LED_PIN_B1, OUTPUT);
        pinMode(STATUS_LED_PIN_B2, OUTPUT);
    }

    void displayErrorCode(byte code)
    {
        display_A.setSegments(_error_segments);
        display_B.showNumberDec(code);

        bool leds_on = _error_blinker.isOn();
        digitalWrite(STATUS_LED_PIN_A1, leds_on);
        digitalWrite(STATUS_LED_PIN_A2, leds_on);
        digitalWrite(STATUS_LED_PIN_B1, leds_on);
        digitalWrite(STATUS_LED_PIN_B2, leds_on);
    }
}