#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "log.h"
#include "display.h"
#include "sensors.h"
#include "config.h"
#include "utils/integrator.h"

enum ErrorCode{
    generic         = 00,
    sensor_init     = 01,
    sd_operation    = 02,
    
};

namespace State
{
    extern bool system_active;
    extern bool qls_open;
    extern bool ref_open;

    extern Integrator ws_integrators[3];

    byte getQlsActiveRoom();
    byte getRefActiveRoom();

    void updateState();

    void throwError(bool code, const char* msg);
}

    // enum ProgState{
    //     active = 0,
    //     pause = 1,
    //     error = 2,
    //     set_active = 10,
    //     set_pause = 11,
    //     set_error = 12,
    // };


    // ProgState _programState = ProgState::set_active;

    // void tickFSM()
    // {
    //     switch (_programState)
    //     {
    //     case ProgState::set_active:
    //         _programState = ProgState::active;
    //         break;
        
    //     case ProgState::active:
            
    //         break;


    //     case ProgState::set_error:
    //         _programState = ProgState::error;
    //         break;
        
    //     case ProgState::error:
    //         Display::displayErrorCode(_error_code);
    //         break;


    //     default:
    //         //throwError
    //     }
    // }



#endif

