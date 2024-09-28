#include <Arduino.h>
#include "drivers/tsl.h"
#include "drivers/vcSensor.h"
#include "log.h"
#include "drivers/rtc.h"
#include "display.h"
#include "sensors.h"
#include "lights.h"
#include "regulators/regulator.h"
#include "server/server.h"

Regulator reg_qls;
Regulator reg_ref;

unsigned long loop_start_time;
unsigned int last_loop_time=100;
unsigned long last_log_event;

void setup(void) 
{
  Serial.begin(115200);
  Wire.begin(21,22,400000);
  delay(500);

  Display::begin();
  Log::begin();
  Rtc::begin();
  Sensors::begin();
  Lights::begin();
  WebServer::begin();

  Serial.println("SETUP DONE");
}

void loop(void) 
{
  loop_start_time = millis();

  //update
  State::updateState();
  Sensors::readAll();

  //log
  if(millis() - last_log_event > LOG_INTERVAL)
  {
    Log::saveAllData();
    last_log_event = millis();
  }

  //control
  if(State::system_active)
  {
    Sensors::CombinedTslData sensor_data = Sensors::getCombinedTslData();

    int qls_lights_u = reg_qls.regulate_PID(300,sensor_data.min_active_qls, last_loop_time);
    int ref_lights_u = reg_ref.regulate_PID(500,sensor_data.min_active_ref, last_loop_time);

    Lights::setValuesForActiveRooms(qls_lights_u, ref_lights_u);

    Serial.print(sensor_data.min_active_qls);
    Serial.print("\t");
    Serial.print(qls_lights_u);
    Serial.print("\t");
    Serial.print(sensor_data.min_active_ref);
    Serial.print("\t");
    Serial.print(ref_lights_u);
    Serial.print("\n");
  }else
  {
    Lights::turnOff();
  }

  //display & delay
  Display::clearLed();
  delay(100);
  Display::displayStatus();

  //loop time
  last_loop_time = millis() - loop_start_time;
  Serial.print("Loop time: ");
  Serial.println(last_loop_time);

  //integrators
  State::ws_integrators[0].increment(Sensors::vc_sensors[0].power_mW/1000,last_loop_time);
  State::ws_integrators[1].increment(Sensors::vc_sensors[1].power_mW/1000,last_loop_time);
  State::ws_integrators[2].increment(Sensors::vc_sensors[2].power_mW/1000,last_loop_time);
}
