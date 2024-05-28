#include "integrator.h"

void Integrator::increment(float value, int duration_ms){
    if(duration_ms < 0)
        return;
    if(duration_ms > 10*1000)
        return;
    if(value < 0)
        return;

    integr_value += (value*duration_ms/1000);
    time_elapsed_s += duration_ms/1000;
}
void Integrator::clear(){
    integr_value = 0;
    time_elapsed_s = 0;
}
float Integrator::get_value(){
    return integr_value;
}
float Integrator::get_time_elapsed_s(){
    return time_elapsed_s;
}
float Integrator::get_avg_value(){
    return integr_value/time_elapsed_s;
}