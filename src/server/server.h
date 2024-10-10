#ifndef SERVER_H
#define SERVER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "SPIFFS.h"

#include "../sensors.h"
#include "../state.h"
#include "../lights.h"
#include "secrets.h"        //if secrets are not defined duplicate secrets_template.h and rename to secrets.h

//Server hosting for GUI webpage
namespace WebServer
{
    void begin();
    void start();
    void stop();
}





#endif