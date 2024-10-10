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
unsigned long last_log_millis;

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
  WebServer::start();

  Serial.println("SETUP DONE");
}

void loop(void) 
{
  loop_start_time = millis();

  //update
  Sensors::readAll();
  State::updateState();

  //log
  if(millis() - last_log_millis > LOG_INTERVAL)
  {
    State::turbo_integrate();
    Log::saveAllData();
    last_log_millis = millis();
  }

  //control
  if(State::system_active)
  {
    Sensors::CombinedTslData sensor_data = Sensors::getCombinedTslData();

    int qls_lights_u = reg_qls.regulate_PID(QLS_SETPOINT,sensor_data.min_active_qls, last_loop_time);
    int ref_lights_u = reg_ref.regulate_PID(REF_SETPOINT,sensor_data.min_active_ref, last_loop_time);

    Lights::setValuesForActiveRooms(qls_lights_u, ref_lights_u);

  }else
  {
    Lights::turnOff();
  }

  //display & delay
  Display::clearLed();
  delay(DELAY_MS);
  Display::displayState();

  //loop time
  last_loop_time = millis() - loop_start_time;
  Serial.print("Loop time: ");
  Serial.println(last_loop_time);

  //integrators
  State::ws_integrate(last_loop_time);
}
