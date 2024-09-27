#include "sensors.h"
#include "state.h"


namespace Sensors
{                                                //GND        Float         VCC
    Tsl tsl_sensors[ROOM_NUM][TSL_NUM] =    {{Tsl(0,0x29), Tsl(0,0x39), Tsl(0,0x49), Tsl(1,0x29), Tsl(1,0x39), Tsl(1,0x49)},     //room 0
                                            {Tsl(2,0x29), Tsl(2,0x39), Tsl(2,0x49), Tsl(3,0x29), Tsl(3,0x39), Tsl(3,0x49)},     //room 1
                                            {Tsl(4,0x29), Tsl(4,0x39), Tsl(4,0x49), Tsl(5,0x29), Tsl(5,0x39), Tsl(5,0x49)},     //room 2
                                            {Tsl(6,0x29), Tsl(6,0x39), Tsl(6,0x49), Tsl(7,0x29), Tsl(7,0x39), Tsl(7,0x49)}};    //room 3
    
                                    //GND,GND        GND, VCC         VCC, GND
    VcSensor vc_sensors[VC_NUM] = {VcSensor(0x40), VcSensor(0x44), VcSensor(0x41)};


    void begin()
    {
        for (int r = 0; r < 4; r++) {
            for (int t = 0; t < TSL_NUM; t++){
                tsl_sensors[r][t].begin();
            }
        }

        for (int i = 0; i < VC_NUM; i++){
            vc_sensors[i].begin();
        }
    }

    void readAll()
    {
        for (int r = 0; r < 4; r++) {
            for (int t = 0; t < TSL_NUM; t++){
                tsl_sensors[r][t].read_lux();
                // Serial.print("|");
            }
        }
        // Serial.println(" ");

        for (int i = 0; i < VC_NUM; i++){
            vc_sensors[i].read();
        }
    }

    void printRoom(int room_id)
    {
        for (size_t i = 0; i < TSL_NUM; i++)
        {
            Serial.print(tsl_sensors[room_id][i].val_lux);
            Serial.print("\t");
        }
    }

    CombinedTslData getCombinedTslData()
    {
        CombinedTslData data;
        float curr_val;

        data.min_active_qls = 100000;
        for (int t = 0; t < TSL_NUM; t++){
            curr_val = tsl_sensors[State::getQlsActiveRoom()][t].val_lux;
            if(curr_val < data.min_active_qls) data.min_active_qls = curr_val;
        }

        data.min_active_ref = 100000;
        for (int t = 0; t < TSL_NUM; t++){
            curr_val = tsl_sensors[State::getRefActiveRoom()][t].val_lux;
            if(curr_val < data.min_active_ref) data.min_active_ref = curr_val;
        }

        data.max_open_qls = 0;
        for (int t = 0; t < TSL_NUM; t++){
            curr_val = tsl_sensors[0][t].val_lux;
            if(curr_val > data.max_open_qls) data.max_open_qls = curr_val;
        }

        data.max_open_ref = 0;
        for (int t = 0; t < TSL_NUM; t++){
            curr_val = tsl_sensors[2][t].val_lux;
            if(curr_val > data.max_open_ref) data.max_open_ref = curr_val;
        }

        return data;
    }
}