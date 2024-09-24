#ifndef LOG_H
#define LOG_H

#include "RTClib.h"
#include <SPI.h>
#include "SdFat.h"
#include "state.h"
#include "sensors.h"
#include "lights.h"
#include "drivers/rtc.h"

#define SD_CS_PIN 5
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16))

namespace Log
{
    extern SdFs sd;

    void begin();

    void saveAllData();

    void saveErrorInfo(byte code, const char* msg);
}



#endif