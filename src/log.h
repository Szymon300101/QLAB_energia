#ifndef LOG_H
#define LOG_H

#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 4

namespace Log
{
    RTC_DS1307 rtc;

    bool _tryReadTimeFromFile()
    {
        if(!SD.exists("time.txt"))
            return false;

        File file = SD.open("time.txt", FILE_READ);

        if (!file) {
            Serial.println("ERROR: Failed to open time file.");
            return false;
        }

        char timestampBuffer[20];
        file.readBytesUntil('\n', timestampBuffer, 20);
        file.close();

        int year, month, day, hour, minute, second;
        if (sscanf(timestampBuffer, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minute, &second) != 6)
        {
            Serial.print("ERROR: Bad dateTime format in 'time.txt' file.");
            return false;
        }

        rtc.adjust(DateTime(year, month, day, hour, minute, second));
        DateTime timeNow = rtc.now();

        Serial.print("Set RTC time from file: ");
        Serial.print(timeNow.year());      Serial.print("-");
        Serial.print(timeNow.month());     Serial.print("-");
        Serial.print(timeNow.day());       Serial.print(" ");
        Serial.print(timeNow.hour());      Serial.print(":");
        Serial.print(timeNow.minute());    Serial.print(":");
        Serial.println(timeNow.second());

        SD.remove("time.txt");

        return true;
    }

    void _filePrintDateTime(File logFile)
    {
        DateTime timeNow = rtc.now();

        logFile.print(timeNow.year());      logFile.print("-");
        logFile.print(timeNow.month());     logFile.print("-");
        logFile.print(timeNow.day());       logFile.print(" ");
        logFile.print(timeNow.hour());      logFile.print(":");
        logFile.print(timeNow.minute());    logFile.print(":");
        logFile.print(timeNow.second());
    }

    bool begin()
    {
        if (!rtc.begin()) {
            Serial.println("ERROR: RTC not connected.");
            return false;
        }
        if (!SD.begin(SD_CS_PIN)) {
            Serial.println("ERROR: SD not connected.");
            return false;
        }

        _tryReadTimeFromFile();

        if(!rtc.isrunning()){
            Serial.println("ERROR: RTC not running.");
            return false;
        }

        return true;
    }

    void saveAllData()
    {
        File logFile = SD.open("Data.txt", FILE_WRITE);
        DateTime timeNow = rtc.now();

        if(!logFile)
        {
            Serial.println("ERROR: Can't open log file.");
            return;
        }

        //print dateTime
        _filePrintDateTime(logFile);    logFile.print("; ");



        logFile.close();
    }

    void saveErrorInfo(byte code, const char* msg)
    {
        File logFile = SD.open("ErrorLog.txt", FILE_WRITE);

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
}



#endif