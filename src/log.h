#ifndef LOG_H
#define LOG_H

#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
#include "state.h"

#define SD_CS_PIN 4

namespace Log
{
    extern RTC_DS1307 rtc;

    bool _tryReadTimeFromFile();

    void _filePrintDateTime(File logFile);

    bool begin();

    void saveAllData();

    void saveErrorInfo(byte code, const char* msg);
}



#endif