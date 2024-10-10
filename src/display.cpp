#include "display.h"

namespace Display
{
    TM1637Display display_A = TM1637Display(4, 13); // CLK_PIN, DIO_PIN
    TM1637Display display_B = TM1637Display(17, 16); // CLK_PIN, DIO_PIN

    Blinker _error_blinker = Blinker(500, 2000);

    const uint8_t _error_segments[] = {
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, // E
        SEG_E | SEG_G,                         // r
        SEG_E | SEG_G,                         // r
        0
    };

    void begin()
    {
        display_A.setBrightness(DISPLAY_BRIGHTNESS);
        display_B.setBrightness(DISPLAY_BRIGHTNESS);

        pinMode(STATUS_LED_PIN_A1, OUTPUT);
        pinMode(STATUS_LED_PIN_A2, OUTPUT);
        pinMode(STATUS_LED_PIN_B1, OUTPUT);
        pinMode(STATUS_LED_PIN_B2, OUTPUT);

        
        display_A.showNumberDec(2222);
        display_B.showNumberDec(1111);

        digitalWrite(STATUS_LED_PIN_A1, HIGH);
        digitalWrite(STATUS_LED_PIN_A2, HIGH);
        digitalWrite(STATUS_LED_PIN_B1, HIGH);
        digitalWrite(STATUS_LED_PIN_B2, HIGH);

        delay(500);

        clearLed();
    }

    void displayState()
    {
        display_A.showNumberDec(Sensors::vc_sensors[0].power_mW + Sensors::vc_sensors[2].power_mW);
        display_B.showNumberDec(Sensors::vc_sensors[1].power_mW);

        digitalWrite(STATUS_LED_PIN_A1,  State::qls_open);
        digitalWrite(STATUS_LED_PIN_A2, !State::qls_open);
        digitalWrite(STATUS_LED_PIN_B1,  State::ref_open);
        digitalWrite(STATUS_LED_PIN_B2, !State::ref_open);
    }

    void displayErrorCode(byte code)
    {
        display_B.setSegments(_error_segments);
        display_A.showNumberDec(code);

        bool leds_on = _error_blinker.isOn();
        digitalWrite(STATUS_LED_PIN_A1, leds_on);
        digitalWrite(STATUS_LED_PIN_A2, leds_on);
        digitalWrite(STATUS_LED_PIN_B1, leds_on);
        digitalWrite(STATUS_LED_PIN_B2, leds_on);
    }

    void clearLed()
    {
        digitalWrite(STATUS_LED_PIN_A1, LOW);
        digitalWrite(STATUS_LED_PIN_A2, LOW);
        digitalWrite(STATUS_LED_PIN_B1, LOW);
        digitalWrite(STATUS_LED_PIN_B2, LOW);
    }
}