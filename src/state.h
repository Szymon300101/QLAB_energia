#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "log.h"
#include "display.h"

namespace State
{
    enum ProgState{
        active = 0,
        pause = 1,
        error = 2,
        set_active = 10,
        set_pause = 11,
        set_error = 12,
    };

    ProgState _programState = ProgState::set_active;
    byte _error_code = 0;

    void tickFSM()
    {
        switch (_programState)
        {
        case ProgState::set_active:
            _programState = ProgState::active;
            break;
        
        case ProgState::active:
            
            break;


        case ProgState::set_error:
            _programState = ProgState::error;
            break;
        
        case ProgState::error:
            Display::displayErrorCode(_error_code);
            break;


        default:
            //throwError
        }
    }

    void throwError(bool code, const char* msg)
    {
        Serial.print("ERROR: ");
        Serial.println(msg);

        Log::saveErrorInfo(code, msg);

        _error_code = code;

        _programState = set_error; //stop program
    }
}





#endif