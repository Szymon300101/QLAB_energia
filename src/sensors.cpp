#include "sensors.h"
#include "state.h"


namespace Sensors
{                                                //GND        Float         VCC
    Tsl tsl_sensors[ROOM_NUM][TSL_NUM] =    {{Tsl(0,0x29), Tsl(0,0x39), Tsl(0,0x49), Tsl(1,0x29), Tsl(1,0x39), Tsl(1,0x49)},     //room 0
                                            {Tsl(2,0x29), Tsl(2,0x39), Tsl(2,0x49), Tsl(3,0x29), Tsl(3,0x39), Tsl(3,0x49)},     //room 1
                                            {Tsl(4,0x29), Tsl(5,0x39), Tsl(4,0x49), Tsl(5,0x29), Tsl(5,0x39), Tsl(5,0x49)},     //room 2
                                            {Tsl(6,0x29), Tsl(6,0x39), Tsl(6,0x49), Tsl(7,0x29), Tsl(7,0x39), Tsl(7,0x49)}};    //room 3
    
                                    //GND,GND        GND, VCC         VCC, GND
    VcSensor vc_sensors[VC_NUM] = {VcSensor(0x40), VcSensor(0x41), VcSensor(0x44)};


    void begin()
    {
        tsl_sensors[0][0].begin();
        tsl_sensors[0][1].begin();
        tsl_sensors[0][2].begin();
        tsl_sensors[0][3].begin();
        tsl_sensors[0][4].begin();
        tsl_sensors[0][5].begin();
        vc_sensors[0].begin();

        // for (int r = 0; r < ROOM_NUM; r++) {
        //     for (int t = 0; t < TSL_NUM; t++){
        //         tslSensors[r][t].begin();
        //     }
        // }

        // for (int i = 0; i < VC_NUM; i++){
        //     vcSensors[i].begin();
        // }
    }

    void readAll()
    {
        for (int r = 0; r < ROOM_NUM; r++) {
            for (int t = 0; t < TSL_NUM; t++){
                tsl_sensors[r][t].read_lux();
            }
        }

        for (int i = 0; i < VC_NUM; i++){
            vc_sensors[i].read();
        }
    }

    CombinedTslData getCombinedTslData()
    {
        CombinedTslData data;
        float curr_val;

        data.avg_active_qls = 0;
        data.max_active_qls = 0;
        for (int t = 0; t < TSL_NUM; t++){
            curr_val = tsl_sensors[State::getQlsActiveRoom()][t].val_lux;
            data.avg_active_qls += curr_val;
            if(curr_val > data.max_active_qls) data.max_active_qls = curr_val;
        }
        data.avg_active_qls /= TSL_NUM;

        data.avg_active_ref = 0;
        data.max_active_ref = 0;
        for (int t = 0; t < TSL_NUM; t++){
            curr_val = tsl_sensors[State::getRefActiveRoom()][t].val_lux;
            data.avg_active_ref += curr_val;
            if(curr_val > data.max_active_ref) data.max_active_ref = curr_val;
        }
        data.avg_active_ref /= TSL_NUM;

        return data;
    }
}