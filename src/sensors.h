#ifndef SENSORS_H
#define SENSORS_H

#include "drivers/tsl.h"
#include "drivers/vcSensor.h"

#define ROOM_NUM 4
#define TSL_NUM 6
#define VC_NUM 3

namespace Sensors
{
    struct CombinedTslData
    {
        float min_active_qls;
        float min_active_ref;
        
        float max_open_qls;
        float max_open_ref;
    };

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
    extern Tsl tsl_sensors[ROOM_NUM][TSL_NUM];

    //addresses set up in 'sensors.cpp'
    extern VcSensor vc_sensors[VC_NUM];

    void begin();

    void readAll();

    void printRoom(int room_id);

    CombinedTslData getCombinedTslData();

    float getRoomAvg(int room_id);
}




#endif