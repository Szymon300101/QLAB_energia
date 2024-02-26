#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "log.h"
#include "display.h"

namespace State
{
    void throwError(bool code, const char* msg)
    {
        Serial.print("ERROR: ");
        Serial.println(msg);

        Log::saveErrorInfo(code, msg);

        Display::setErrorCode(code);

        //go to halt
    }
}





#endif