#ifndef INTEGRATOR_H
#define INTEGRATOR_H

//Class for integrating mesurement over time.
//For example integrates W and ms to W*s
class Integrator
{
    float integr_value;
    float time_elapsed_s;
public:
    void increment(float value, int duration_ms);
    void clear();
    float get_value();
    float get_time_elapsed_s();
    float get_avg_value();
};









#endif