#include "state.h"


namespace State
{
    bool system_active = true;
    bool qls_open = true;
    bool ref_open = true;

    Integrator ws_integrators[3] = {Integrator(),Integrator(),Integrator()};
    TurboIntegrator turbo_integrators[3] = {TurboIntegrator('0'),TurboIntegrator('1'),TurboIntegrator('2')};
    
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

        if(Rtc::isWorkTime())
        {
            system_active = true;
            if(qls_open)
            {
                
                if(sensor_data.max_open_qls > BLIND_CLOSE_TRES)
                {
                    qls_open = false;
                }
                // if(sensor_data.max_open_qls > BLIND_CLOSE_TRES)
                // {
                //     if(qls_last_state_change_time > 0 && (millis() - qls_last_state_change_time > ROOM_STATE_HYSTERESIS_TIME))
                //     {
                //         qls_open = false;
                //         qls_last_state_change_time = 0;
                //     }else if(qls_last_state_change_time == 0)
                //     {
                //         qls_last_state_change_time = millis();
                //     }
                // }else
                // {
                //     qls_last_state_change_time = 0;
                // }
                
            }else
            {
                if(sensor_data.max_open_qls < BLIND_OPEN_TRES)
                {
                    qls_open = true;
                }
            }

            if(ref_open)
            {
                if(sensor_data.max_open_ref > BLIND_CLOSE_TRES)
                {
                    ref_open = false;
                }
            }else
            {
                if(sensor_data.max_open_ref < BLIND_OPEN_TRES)
                {
                    ref_open = true;
                }
            }

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

    void ws_integrate(unsigned int last_loop_time)
    {
        State::ws_integrators[0].increment(Sensors::vc_sensors[0].power_mW/1000,last_loop_time);
        State::ws_integrators[1].increment(Sensors::vc_sensors[1].power_mW/1000,last_loop_time);
        State::ws_integrators[2].increment(Sensors::vc_sensors[2].power_mW/1000,last_loop_time);
    }

    void turbo_integrate()
    {
        State::turbo_integrators[0].increment(State::ws_integrators[0].get_value());
        State::turbo_integrators[1].increment(State::ws_integrators[1].get_value());
        State::turbo_integrators[2].increment(State::ws_integrators[2].get_value());
    }
}