#include "state.h"


namespace State
{
    void throwError(bool code, const char* msg)
    {
        //log error
        Serial.print("ERROR: ");
        Serial.println(msg);
        Log::saveErrorInfo(code, msg);

        //clean up


        //halt
        while(1)
        {
            Display::displayErrorCode(code);
            delay(10);
        }
    }
}