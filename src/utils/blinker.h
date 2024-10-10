#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>

//class for semi-asynchronous led blinking
//tick() or isOn() need to be called relatevly often to achive accouracy
class Blinker
{
    bool _blink_on=false;
    unsigned long _last_blink_time=0;
    int _on_time;
    int _off_time;

public:
    Blinker(int on_time, int off_time)
    {
        _on_time = on_time;
        _off_time = off_time;
    }

    void tick()
    {
        if(_blink_on)
        {
            if(millis() > _last_blink_time + _on_time)
            {
                _last_blink_time = millis();
                _blink_on = false;
            }
        }else
        {
            if(millis() > _last_blink_time + _off_time)
            {
                _last_blink_time = millis();
                _blink_on = true;
            }
        }
    }

    bool isOn()
    {
        tick();
        return _blink_on;
    }
};


#endif