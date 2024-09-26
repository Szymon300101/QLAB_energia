#ifndef SERVER_H
#define SERVER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "SPIFFS.h"

#include "../sensors.h"
#include "secrets.h"        //if secrets are not defined duplicate secrets_template.h and rename to secrets.h

namespace WebServer
{

    void begin();

}





#endif