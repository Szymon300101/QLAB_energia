#include "turboIntegrator.h"


TurboIntegrator::TurboIntegrator(char uid)
{
    UID = uid;

    prefs.begin("TurboIntegrator",true);
    integr_value = prefs.getDouble(&UID,0);
    prefs.end();
}

void TurboIntegrator::increment(double value){

    integr_value += value;

    prefs.begin("TurboIntegrator");
    prefs.putDouble(&UID,integr_value);
    prefs.end();
}

void TurboIntegrator::clear(){
    integr_value = 0;
    
    prefs.begin("TurboIntegrator");
    prefs.putDouble(&UID,0);
    prefs.end();
}

float TurboIntegrator::get_value(){
    return integr_value;
}