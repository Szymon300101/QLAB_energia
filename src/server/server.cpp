#include "server.h"


namespace WebServer
{

    AsyncWebServer server(80);

    String templateProcessor(const String& var)
    {
        if(var == "HELLO_FROM_TEMPLATE")
            return (String) Sensors::vc_sensors[0].power_mW;
        return String();
    }

    void begin()
    {
        if(!SPIFFS.begin(false)){
            Serial.println("SPIFFS Mount Failed");
            return;
        }
        // Connect to Wi-Fi
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

        // Start the server
        server.begin();
    }
}