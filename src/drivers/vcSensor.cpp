#include "vcSensor.h"
#include "../state.h"

VcSensor::VcSensor(byte i2c_addr) : ina219(i2c_addr)
{
    _i2c_addr = i2c_addr;
}

bool VcSensor::begin()
{
    if (!ina219.begin()) {
        State::throwError(ErrorCode::sensor_init, "Failed to find INA219 with address: " + _i2c_addr);
        return false;
    }

    return true;
}

void VcSensor::read()
{
    shuntvoltage_mV = ina219.getShuntVoltage_mV();
    busvoltage_V = ina219.getBusVoltage_V();
    current_mA = max(0.0F,ina219.getCurrent_mA());
    power_mW = max(0.0F,ina219.getPower_mW());
    loadvoltage_V = busvoltage_V + (shuntvoltage_mV / 1000);
}