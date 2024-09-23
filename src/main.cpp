#include <Arduino.h>
#include "drivers/tsl.h"
#include "drivers/vcSensor.h"
#include "log.h"
#include "display.h"
#include "sensors.h"
#include "lights.h"
#include "regulators/regulator.h"

Regulator reg_qls;
Regulator reg_ref;

unsigned long loop_start_time;
unsigned int last_loop_time=100;

void setup(void) 
{
  Serial.begin(115200);
  Wire.begin(21,22,400000);
  delay(5000);

  // Display::begin();
  Log::begin();
  Sensors::begin();
  Lights::begin();

  Serial.println("SETUP DONE");

  State::qls_open=true;
  // State::ref_open=true;
  Lights::setValuesForActiveRooms(128, 128);
}

void loop(void) 
{
  loop_start_time = millis();

  // Serial.print(Sensors::tsl_sensors[0][0].read_lux());
  // Serial.print("   ");
  // Serial.print(Sensors::tsl_sensors[0][1].read_lux());
  // Serial.print("   ");
  // Serial.print(Sensors::tsl_sensors[0][2].read_lux());
  // Serial.print("   ");
  // Serial.print(Sensors::tsl_sensors[0][3].read_lux());
  // Serial.print("   ");
  // Serial.print(Sensors::tsl_sensors[0][4].read_lux());
  // Serial.print("   ");
  // Serial.print(Sensors::tsl_sensors[0][5].read_lux());
  // Serial.print("   ");

  Sensors::readAll();
  // Sensors::printRoom(0);
  // Serial.print("|||\t");
  // Sensors::printRoom(1);
  // Serial.print("|||\t");
  // Sensors::printRoom(2);
  // Serial.print("|||\t");
  // Sensors::printRoom(3);

  // Serial.print(Sensors::vc_sensors[0].busvoltage_V);
  // Serial.print("   ");
  // Serial.println(Sensors::vc_sensors[0].current_mA);

  // Serial.print("|\t");
  // State::qls_open=false;
  // Sensors::CombinedTslData sensor_data = Sensors::getCombinedTslData();
  // Serial.print(sensor_data.avg_active_qls);
  // Serial.print("|\t");
  
  // State::qls_open=true;
  // sensor_data = Sensors::getCombinedTslData();
  // Serial.print(sensor_data.avg_active_qls);
  // Serial.println(" ");

  Sensors::CombinedTslData sensor_data = Sensors::getCombinedTslData();

  int qls_lights_u = reg_qls.regulate_PID(300,sensor_data.avg_active_qls, last_loop_time);
  int ref_lights_u = reg_ref.regulate_PID(500,sensor_data.avg_active_ref, last_loop_time);

  Lights::setValuesForActiveRooms(qls_lights_u, ref_lights_u);

  Serial.print(sensor_data.avg_active_qls);
  Serial.print("\t");
  Serial.print(qls_lights_u);
  Serial.print("\t");
  Serial.print(sensor_data.avg_active_ref);
  Serial.print("\t");
  Serial.print(ref_lights_u);
  Serial.print("\n");


  // 

  // Serial.print(500);
  // Serial.print(" ");
  // Serial.print(sensor_data.avg_active_qls);
  // Serial.print(" ");
  // Serial.print(qls_lights_u);
  // Serial.println("");

  delay(100);

  last_loop_time = millis() - loop_start_time;

  // Serial.print("Loop time: ");
  // Serial.println(last_loop_time);

  State::ws_integrators[0].increment(Sensors::vc_sensors[0].power_mW/1000,last_loop_time);
  State::ws_integrators[1].increment(Sensors::vc_sensors[1].power_mW/1000,last_loop_time);
  State::ws_integrators[2].increment(Sensors::vc_sensors[2].power_mW/1000,last_loop_time);
}
