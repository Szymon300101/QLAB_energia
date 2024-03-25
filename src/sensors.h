#ifndef SENSORS_H
#define SENSORS_H

#include "tsl.h"
#include "vcSensor.h"

#define ROOM_NUM 4
#define TSL_NUM 6
#define VC_NUM 3

namespace Sensors
{
    //ADDRESSING CONVENTION
    /*
        sensors IDs in room (looking from the top):
                            _______ wall ______
                            |                 |
                            |   0         3   |
                            |                 |
                            |   1         4   |
                            |                 |
                            |   2         5   |
                            |                 |
                            ^^^^^ window ^^^^^^
        room IDs:
        0 - QLS open
        1 - QLS closed
        2 - conventional open
        3 - conventional closed
    
        voltage sensors IDs:
        0 - QLS     - room 0, 1
        1 - conv.   - room 2, 3
        2 - QLS parrots
    */

    //addresses set up in 'sensors.cpp'
    extern Tsl tslSensors[ROOM_NUM][TSL_NUM];

    //addresses set up in 'sensors.cpp'
    extern VcSensor vcSensors[VC_NUM];

    void begin();
}




#endif