#include "state.h"


namespace State
{
    bool system_active = true;
    bool qls_open = true;
    bool ref_open = true;

    unsigned long qls_last_state_change_time = 0;
    unsigned long ref_last_state_change_time = 0;

    extern Integrator ws_integrators[4] = {Integrator(),Integrator(),Integrator(),Integrator()};
    
    byte getQlsActiveRoom()
    {
        return qls_open ? 0 : 1;
    }
    
    byte getRefActiveRoom()
    {
        return ref_open ? 2 : 3;
    }

    void updateState()
    {
        Sensors::CombinedTslData sensor_data = Sensors::getCombinedTslData();

        if(Log::isWorkTime())
        {
            system_active = true;
            if(qls_open)
            {
                if(sensor_data.max_open_qls > BLIND_CLOSE_TRES && (millis() - qls_last_state_change_time < ROOM_STATE_HYSTERESIS_TIME))
                {
                    qls_open = false;
                    qls_last_state_change_time = millis();
                }
            }else
            {
                if((sensor_data.max_open_qls < BLIND_OPEN_TRES && (millis() - qls_last_state_change_time < ROOM_STATE_HYSTERESIS_TIME)))
                {
                    qls_open = true;
                    qls_last_state_change_time = millis();
                }
            }

            //same for ref

        }else{
            system_active = false;
            qls_open = true;
            ref_open = true;
        }
    }

    void throwError(bool code, const char* msg)
    {
        //log error
        Serial.print("ERROR: ");
        Serial.println(msg);
        Log::saveErrorInfo(code, msg);

        //clean up
        Lights::turnOff();

        //halt
        while(1)
        {
            Display::displayErrorCode(code);
            delay(10);
        }
    }
}