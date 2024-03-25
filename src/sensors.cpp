#include "sensors.h"


namespace Sensors
{                                                //GND        Float         VCC
    Tsl tslSensors[ROOM_NUM][TSL_NUM] =    {{Tsl(0,0x29), Tsl(0,0x39), Tsl(0,0x49), Tsl(1,0x29), Tsl(1,0x39), Tsl(1,0x49)},     //room 0
                                            {Tsl(2,0x29), Tsl(2,0x39), Tsl(2,0x49), Tsl(3,0x29), Tsl(3,0x39), Tsl(3,0x49)},     //room 1
                                            {Tsl(4,0x29), Tsl(5,0x39), Tsl(4,0x49), Tsl(5,0x29), Tsl(5,0x39), Tsl(5,0x49)},     //room 2
                                            {Tsl(6,0x29), Tsl(6,0x39), Tsl(6,0x49), Tsl(7,0x29), Tsl(7,0x39), Tsl(7,0x49)}};    //room 3
    
                                    //GND,GND        GND, VCC         VCC, GND
    VcSensor vcSensors[VC_NUM] = {VcSensor(0x40), VcSensor(0x41), VcSensor(0x44)};


    void begin()
    {
        tslSensors[0][1].begin();
        vcSensors[0].begin();

        // for (int r = 0; r < ROOM_NUM; r++) {
        //     for (int t = 0; t < TSL_NUM; t++){
        //         tslSensors[r][t].begin();
        //     }
        // }

        // for (int i = 0; i < VC_NUM; i++){
        //     vcSensors[i].begin();
        // }
    }
}