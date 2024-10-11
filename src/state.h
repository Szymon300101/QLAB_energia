#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "log.h"
#include "display.h"
#include "sensors.h"
#include "config.h"
#include "utils/integrator.h"
#include "utils/turboIntegrator.h"

enum ErrorCode{
    generic         = 00,
    sensor_init     = 01,
    sd_operation    = 02,
    
};

//Simpel app state menager
namespace State
{
    extern bool system_active;
    extern bool qls_open;
    extern bool ref_open;

    extern Integrator ws_integrators[3];
    extern TurboIntegrator turbo_integrators[3];

    byte getQlsActiveRoom();
    byte getRefActiveRoom();

    void begin();

    void updateState();

    void throwError(bool code, const char* msg);

    void ws_integrate(unsigned int last_loop_time);
    void turbo_integrate();
}

#endif
