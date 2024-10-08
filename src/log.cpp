#include "log.h"


namespace Log
{
    SdFs sd;
    
    void begin()
    {
        if (!(sd.cardBegin(SD_CONFIG) && sd.volumeBegin())) {
            State::throwError(ErrorCode::sd_operation, "SD not connected.");
        }

        if(!sd.exists("Data.txt")) //simple way to clear turbo integrators in runtime
        {
            State::turbo_integrators[0].clear();
            State::turbo_integrators[1].clear();
            State::turbo_integrators[2].clear();
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

        Serial.print("Saving log...  ");

        //print dateTime
        Rtc::filePrintDateTime(&logFile);    logFile.print("; ");

        //print state
        logFile.print(State::system_active);        logFile.print("; ");
        logFile.print(State::qls_open);             logFile.print("; ");
        logFile.print(State::ref_open);             logFile.print("; ");

        //print lights values
        logFile.print(Lights::values[0]);           logFile.print("; ");
        logFile.print(Lights::values[1]);           logFile.print("; ");
        logFile.print(Lights::values[2]);           logFile.print("; ");
        logFile.print(Lights::values[3]);           logFile.print("; ");
        logFile.print(Lights::parrot_values[0]);    logFile.print("; ");
        logFile.print(Lights::parrot_values[1]);    logFile.print("; ");

        //print light sensors
        for (int r = 0; r < ROOM_NUM; r++) {
            for (int t = 0; t < TSL_NUM; t++) {
                logFile.print(Sensors::tsl_sensors[r][t].val_lux);  logFile.print("; ");
            }
        }

        //print current sensors
        for (int i = 0; i < VC_NUM; i++)
        {
            logFile.print(Sensors::vc_sensors[i].loadvoltage_V,3);     logFile.print("; ");
            logFile.print(Sensors::vc_sensors[i].current_mA,3);        logFile.print("; ");
        }

        //print integrators
        for (int i = 0; i < 3; i++)
        {
            logFile.print(State::ws_integrators[i].get_value(),3);        logFile.print("; ");  //W*s
            logFile.print(State::ws_integrators[i].get_time_elapsed_s()); logFile.print("; ");  //s
            State::ws_integrators[i].clear();
        }

        //print turbo integrators
        for (int i = 0; i < 3; i++)
        {
            logFile.print(State::turbo_integrators[i].get_value(),3);        logFile.print("; ");  //W*s
        }

        logFile.println(" ");
        logFile.close();
        
        Serial.println("Log saved.");
    }

    void saveErrorInfo(byte code, const char* msg)
    {
        FsFile logFile = sd.open("ErrorLog.txt", FILE_WRITE);

        if(!logFile)
        {
            //if can't log, don't log
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