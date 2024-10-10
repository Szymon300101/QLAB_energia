#include "server.h"


namespace WebServer
{

    AsyncWebServer server(80);

    String _templateProcessor(const String& var)
    {
        if(var == "qls_power")
            return String(Sensors::vc_sensors[0].power_mW + Sensors::vc_sensors[2].power_mW,0);
        if(var == "ref_power")
            return String(Sensors::vc_sensors[1].power_mW,0);

        if(var == "qls_integrated")
            return String((State::turbo_integrators[0].get_value() + State::turbo_integrators[2].get_value())/3600,3);
        if(var == "ref_integrated")
            return String(State::turbo_integrators[1].get_value()/3600,3);

        if(var == "qls_open_border")
            return State::qls_open ? "border-active" : "border-inactive";
        if(var == "qls_close_border")
            return State::qls_open ? "border-inactive" : "border-active";
        if(var == "ref_open_border")
            return State::ref_open ? "border-active" : "border-inactive";
        if(var == "ref_close_border")
            return State::ref_open ? "border-inactive" : "border-active";

        if(var.startsWith("tsl_"))
            return String(Sensors::tsl_sensors[var[4]-'0'][var[6]-'0'].val_lux,0);

        if(var.startsWith("room_light_"))
            return String(Lights::values[var[11]-'0']);
            
        if(var == "room_parrot_0")
            return Lights::parrot_values[0]>0 ? "On" : "Off";
        if(var == "room_parrot_1")
            return Lights::parrot_values[1]>0 ? "On" : "Off";
            
        if(var.startsWith("room_avg_"))
            return String(Sensors::getRoomAvg(var[9]-'0'),0);

        Serial.print("Unused template:  ");
        Serial.println(var);
        return String(var);
    }

    void begin()
    {
        if(!SPIFFS.begin(false)){
            Serial.println("SPIFFS Mount Failed");
            return;
        }

        WiFi.setHostname("esp32energia");

        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
            Serial.println("GET /");
            request->send(SPIFFS, "/index.htm", String(), false, _templateProcessor);
        });

        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/style.css", "text/css");
        });
    }

    void start()
    {
        // Connect to Wi-Fi
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        unsigned long connect_start_time = millis();
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting to WiFi...");
            if(millis() - connect_start_time > 60*1000)
            {
                Serial.println("WiFi connection timeout.");
                return;
            }
        }
        Serial.println("Connected to WiFi");

        Serial.print("ESP32 Web Server's IP address: ");
        Serial.println(WiFi.localIP());

        
        server.begin();       
    }

    void stop()
    {
        server.end();
        Serial.println("Stopped Web Server.");
        WiFi.disconnect();
    }
}