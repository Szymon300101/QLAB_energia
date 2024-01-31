#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>    //included locally, because of modified Adafruit_INA219.cpp file.
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <TM1637Display.h>


#define CLK 6
#define DIO 7

Adafruit_INA219 ina219;
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
TM1637Display display(CLK, DIO);

float led_pwm = 10;
float led_p = 0.03;
float setpoint = 500;

void setup(void) 
{
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }
    
  Serial.println("Hello!");

   /* Initialise the sensor */
  //use tsl.begin() to default to Wire, 
  //tsl.begin(&Wire2) directs api to use Wire2, etc.
  if(!tsl.begin())
  {
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  tsl.enableAutoRange(false);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");

  
  display.setBrightness(0x0f);
}

void loop(void) 
{

  sensors_event_t event;
  tsl.getEvent(&event);
 
  /* Display the results (light is measured in lux) */
  if (event.light)
  {
    Serial.print(event.light); Serial.println(" lux");
    // disp_show(event.light);
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }


  // analogWrite(5, map(analogRead(A0), 0, 1025, 0, 200));

  led_pwm += (setpoint - event.light)*led_p;
  led_pwm = min(255, max(0, led_pwm));
  analogWrite(5,led_pwm);

  Serial.print("PWM: ");
  Serial.println(led_pwm);


  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  // Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  // Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  // Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  // Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

  display.showNumberDec(current_mA);

  delay(200);
}
