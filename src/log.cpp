#include "log.h"


namespace Log
{
    SdFs sd;
    
    void begin()
    {
        if (!(sd.cardBegin(SD_CONFIG) && sd.volumeBegin())) {
            State::throwError(ErrorCode::sd_operation, "SD not connected.");
        }
        
    }

    void saveAllData()
    {
        FsFile logFile = sd.open("Data.txt", FILE_WRITE);
        DateTime timeNow = Rtc::rtc.now();

        if(!logFile)
        {
            State::throwError(ErrorCode::sd_operation, "Can't open log file.");
        }

        //print dateTime
        Rtc::filePrintDateTime(&logFile);    logFile.print("; ");

        //print lights values
        logFile.print(Lights::values[0]);           logFile.print("; ");
        logFile.print(Lights::values[1]);           logFile.print("; ");
        logFile.print(Lights::values[2]);           logFile.print("; ");
        logFile.print(Lights::values[3]);           logFile.print("; ");
        logFile.print(Lights::parrot_values[0]);    logFile.print("; ");
        logFile.print(Lights::parrot_values[1]);    logFile.print("; ");

        //print light sensors (Stare odczyty!)
        for (int r = 0; r < ROOM_NUM; r++) {
            for (int t = 0; t < TSL_NUM; t++) {
                logFile.print(Sensors::tsl_sensors[r][t].val_lux);  logFile.print("; ");
            }
        }

        //print current sensors
        for (int i = 0; i < VC_NUM; i++)
        {
            logFile.print(Sensors::vc_sensors[0].loadvoltage_V);     logFile.print("; ");
            logFile.print(Sensors::vc_sensors[0].current_mA);        logFile.print("; ");
            logFile.print(Sensors::vc_sensors[0].power_mW);          logFile.print("; ");
        }
        

        

        logFile.println(" ");
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
        Rtc::filePrintDateTime(&logFile);  logFile.print("; ");
        logFile.print(code);                logFile.print("; ");
        logFile.print(msg);                 logFile.print("; ");

        logFile.println(" ");
        logFile.close();
    }

}