#ifndef RTC_H
#define RTC_H

#include "RTClib.h"
#include "state.h"

namespace Rtc
{
    extern RTC_DS1307 rtc;

    void begin();

    void filePrintDateTime(FsFile *logFile);

    void serialPrintDateTime();

    bool isWorkTime();

    bool _tryReadTimeFromFile();
}




#endif