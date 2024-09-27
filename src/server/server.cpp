#include "server.h"


namespace WebServer
{

    AsyncWebServer server(80);

    String wrapWithPercent(const String& var) {
        char buffer[100];  // Large enough buffer to hold result
        snprintf(buffer, sizeof(buffer), "%%%s%%", var.c_str());  // Similar to sprintf
        return String(buffer);  // Convert buffer to std::string
    }

    String templateProcessor(const String& var)
    {
        if(var == "qls_power")
            return (String) (Sensors::vc_sensors[0].power_mW+Sensors::vc_sensors[2].power_mW);
        if(var == "ref_power")
            return (String) Sensors::vc_sensors[1].power_mW;

        if(var == "qls_open_border")
            return State::qls_open ? "border-active" : "border-inactive";
        if(var == "qls_close_border")
            return State::qls_open ? "border-inactive" : "border-active";
        if(var == "ref_open_border")
            return State::ref_open ? "border-active" : "border-inactive";
        if(var == "ref_close_border")
            return State::ref_open ? "border-inactive" : "border-active";

        if(var.startsWith("tsl_"))
            return (String) Sensors::tsl_sensors[var[4]-'0'][var[6]-'0'].val_lux;

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
        // Connect to Wi-Fi
        WiFi.setHostname("esp32energia");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");

        // Print the ESP32's IP address
        Serial.print("ESP32 Web Server's IP address: ");
        Serial.println(WiFi.localIP());

        // Define a route to serve the HTML page
        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
            Serial.println("GET /");        // for debugging
            request->send(SPIFFS, "/index.htm", String(), false, templateProcessor);
        });

        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/style.css", "text/css");
        });

        // Start the server
        server.begin();
    }
}