#include "rtc.h"



namespace Rtc
{
    RTC_DS1307 rtc;

    void begin()
    {
        if (!rtc.begin()) {
            State::throwError(ErrorCode::sensor_init, "RTC not connected.");
        }

        if(rtc.isrunning() && rtc.now().year()>2000){
            Serial.print("RTC initialized with time: ");
            serialPrintDateTime();
        }else{
            Serial.println("RTC initialized without time.");
        }

        _tryReadTimeFromFile();

        if(!(rtc.isrunning() && rtc.now().year()>2000)){
            State::throwError(ErrorCode::sensor_init, "RTC not running. No time set.");
        }

    }

    void filePrintDateTime(FsFile *logFile)
    {
        DateTime timeNow = rtc.now();

        (*logFile).print(timeNow.year());      (*logFile).print("-");
        (*logFile).print(timeNow.month());     (*logFile).print("-");
        (*logFile).print(timeNow.day());       (*logFile).print(" ");
        (*logFile).print(timeNow.hour());      (*logFile).print(":");
        (*logFile).print(timeNow.minute());    (*logFile).print(":");
        (*logFile).print(timeNow.second());
    }

    void serialPrintDateTime()
    {
        DateTime timeNow = rtc.now();

        Serial.print(timeNow.year());      Serial.print("-");
        Serial.print(timeNow.month());     Serial.print("-");
        Serial.print(timeNow.day());       Serial.print(" ");
        Serial.print(timeNow.hour());      Serial.print(":");
        Serial.print(timeNow.minute());    Serial.print(":");
        Serial.println(timeNow.second());
    }
    
    bool isWorkTime()
    {
        DateTime timeNow = rtc.now();

        if(timeNow.dayOfTheWeek()==0 || timeNow.dayOfTheWeek()==0)
            return false;

        if(timeNow.hour()<DAY_START_HOUR || timeNow.hour()>DAY_END_HOUR)
            return false;

        //holiday???

        return true;
    }

    
    bool _tryReadTimeFromFile()
    {
        if(!Log::sd.exists("time.txt"))
        {
            Serial.println("No time file to read");
            return false;
        }

        FsFile file = Log::sd.open("time.txt", FILE_READ);

        if (!file)
        {
            State::throwError(ErrorCode::sd_operation, "Failed to open time file.");
        }

        char timestampBuffer[20];
        file.readBytesUntil('\n', timestampBuffer, 20);
        file.close();

        int year, month, day, hour, minute, second;
        if (sscanf(timestampBuffer, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minute, &second) != 6)
        {
            State::throwError(ErrorCode::sd_operation, "Bad dateTime format in 'time.txt' file.");
        }

        Rtc::rtc.adjust(DateTime(year, month, day, hour, minute, second));
        
        Serial.print("Set RTC time from file: ");
        Rtc::serialPrintDateTime();

        Log::sd.remove("time.txt");

        return true;
    }

}