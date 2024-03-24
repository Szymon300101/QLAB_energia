#ifndef LOG_H
#define LOG_H

#include "RTClib.h"
#include <SPI.h>
#include "SdFat.h"
#include "state.h"

#define SD_CS_PIN 5
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16))

namespace Log
{
    extern RTC_DS1307 rtc;

    bool _tryReadTimeFromFile();

    void _filePrintDateTime(FsFile logFile);

    void _serialPrintDateTime();

    bool begin();

    void saveAllData();

    void saveErrorInfo(byte code, const char* msg);
}



#endif