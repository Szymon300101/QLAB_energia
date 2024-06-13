#include <Arduino.h>
#include "drivers/tsl.h"
#include "drivers/vcSensor.h"
#include "log.h"
#include "display.h"
#include "sensors.h"
#include "lights.h"
#include "regulators/regulator.h"

Regulator reg1;

unsigned long loop_start_time;
unsigned int last_loop_time=100;

void setup(void) 
{
  Serial.begin(115200);
  delay(5000);

  // Display::begin();
  Log::begin();
  Sensors::begin();
  Lights::begin();

  Serial.println("SETUP DONE");
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

  Sensors::tsl_sensors[0][0].read_lux();
  Sensors::tsl_sensors[0][1].read_lux();
  Sensors::tsl_sensors[0][2].read_lux();
  Sensors::tsl_sensors[0][3].read_lux();
  Sensors::tsl_sensors[0][4].read_lux();
  Sensors::tsl_sensors[0][5].read_lux();

  Sensors::vc_sensors[0].read();
  // Serial.print(Sensors::vc_sensors[0].busvoltage_V);
  // Serial.print("   ");
  // Serial.println(Sensors::vc_sensors[0].current_mA);

  Sensors::CombinedTslData sensor_data = Sensors::getCombinedTslData();

  int qls_lights_u = reg1.regulate_PID(500,sensor_data.avg_active_qls, last_loop_time);

  Lights::setValuesForActiveRooms(qls_lights_u, 0);

  Serial.print(500);
  Serial.print(" ");
  Serial.print(sensor_data.avg_active_qls);
  Serial.print(" ");
  Serial.print(qls_lights_u);
  Serial.println("");


  // tsl_sensor.read_lux();
  // /* Display the results (light is measured in lux) */
  // if (tsl_sensor.val_lux >=0)
  // {
  //   Serial.print(tsl_sensor.val_lux); Serial.println(" lux");
  //   // disp_show(event.light);
  // }
  // else
  // {
  //   /* If event.light = 0 lux the sensor is probably saturated
  //      and no reliable data could be generated! */
  //   Serial.println("Sensor overload");
  // }


  // // analogWrite(5, map(analogRead(A0), 0, 1025, 0, 200));

  // led_pwm += (setpoint - tsl_sensor.val_lux)*led_p;
  // led_pwm = min(255.0f, max(0.0f, led_pwm));
  // analogWrite(5,led_pwm);

  // Serial.print("PWM: ");
  // Serial.println(led_pwm);


  // vc_sensor.read();
  
  // Serial.print("Current:       "); Serial.print(vc_sensor.current_mA); Serial.println(" mA");

  // display.showNumberDec(vc_sensor.current_mA);

  delay(100);

  last_loop_time = millis() - loop_start_time;

  State::ws_integrators[0].increment(Sensors::vc_sensors[0].power_mW/1000,last_loop_time);
}
