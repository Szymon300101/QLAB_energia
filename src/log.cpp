#include "log.h"


namespace Log
{
    RTC_DS1307 rtc;
    SdFs sd;
    
    bool begin()
    {
        if (!rtc.begin()) {
            State::throwError(ErrorCode::sensor_init, "RTC not connected.");
        }

        if(rtc.isrunning()){
            Serial.print("RTC initialized with time: ");
            _serialPrintDateTime();
        }else{
            Serial.println("RTC initialized without time.");
        }

        if (!(sd.cardBegin(SD_CONFIG) && sd.volumeBegin())) {
            State::throwError(ErrorCode::sd_operation, "SD not connected.");
        }

        _tryReadTimeFromFile();

        if(!rtc.isrunning()){
            State::throwError(ErrorCode::sensor_init, "RTC not running. No time set.");
        }

        return true;
    }

    void saveAllData()
    {
        FsFile logFile = sd.open("Data.txt", FILE_WRITE);
        DateTime timeNow = rtc.now();

        if(!logFile)
        {
            State::throwError(ErrorCode::sd_operation, "Can't open log file.");
        }

        //print dateTime
        _filePrintDateTime(logFile);    logFile.print("; ");

        logFile.close();
    }

    void saveErrorInfo(byte code, const char* msg)
    {
        FsFile logFile = sd.open("ErrorLog.txt", FILE_WRITE);

        if(!logFile)
        {
            //supress error
            return;
        }

        //print dateTime
        _filePrintDateTime(logFile);    logFile.print("; ");
        logFile.print(code);            logFile.print("; ");
        logFile.print(msg);            logFile.print("; ");

        logFile.close();
    }

    bool _tryReadTimeFromFile()
    {
        if(!sd.exists("time.txt"))
        {
            Serial.println("No time file to read");
            return false;
        }

        FsFile file = sd.open("time.txt", FILE_READ);

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

        rtc.adjust(DateTime(year, month, day, hour, minute, second));
        
        Serial.print("Set RTC time from file: ");
        _serialPrintDateTime();

        sd.remove("time.txt");

        return true;
    }

    void _filePrintDateTime(FsFile logFile)
    {
        DateTime timeNow = rtc.now();

        logFile.print(timeNow.year());      logFile.print("-");
        logFile.print(timeNow.month());     logFile.print("-");
        logFile.print(timeNow.day());       logFile.print(" ");
        logFile.print(timeNow.hour());      logFile.print(":");
        logFile.print(timeNow.minute());    logFile.print(":");
        logFile.print(timeNow.second());
    }

    void _serialPrintDateTime()
    {
        DateTime timeNow = rtc.now();

        Serial.print(timeNow.year());      Serial.print("-");
        Serial.print(timeNow.month());     Serial.print("-");
        Serial.print(timeNow.day());       Serial.print(" ");
        Serial.print(timeNow.hour());      Serial.print(":");
        Serial.print(timeNow.minute());    Serial.print(":");
        Serial.println(timeNow.second());
    }
}