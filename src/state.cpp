#include "state.h"


namespace State
{
    bool qls_open = true;
    bool ref_open = true;

    extern Integrator ws_integrators[4] = {Integrator(),Integrator(),Integrator(),Integrator()};
    
    byte getQlsActiveRoom()
    {
        return qls_open ? 0 : 1;
    }
    
    byte getRefActiveRoom()
    {
        return ref_open ? 2 : 3;
    }

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