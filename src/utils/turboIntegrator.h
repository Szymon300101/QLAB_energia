#ifndef TURBO_INTEGRATOR_H
#define TURBO_INTEGRATOR_H

#include <Arduino.h>
#include <Preferences.h>

//Class calculating a sum of given value "from beggining of time". The sum is retained between power cycles.
//Doesn't do full integration like Integrator.h, just adds new value to the old value.
class TurboIntegrator
{
    char UID; //unique id of this integrator. Will save Preferences using this id.
    double integr_value;
    Preferences prefs;

public:
    TurboIntegrator(char uid);
    void begin();
    void increment(double value);
    void clear();
    float get_value();
};









#endif