#include <Arduino.h>
#include <TM1637Display.h>
#include "tsl.h"
#include "vcSensor.h"
#include "log.h"
#include "display.h"


#define CLK 6
#define DIO 7

Tsl tsl_sensor = Tsl(1,0x39);
VcSensor vc_sensor = VcSensor(0x70);

TM1637Display display(CLK, DIO);

float led_pwm = 10;
float led_p = 0.03;
float setpoint = 500;

void setup(void) 
{
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  delay(5000);
    
  // Serial.println("Hello!");

  Display::begin();
  tsl_sensor.begin();
  vc_sensor.begin();
  Log::begin();

  
  display.setBrightness(0x0f);


}

void loop(void) 
{

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

  delay(200);
}
