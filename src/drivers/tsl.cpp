#include "tsl.h"
#include "../state.h"

Tsl::Tsl(byte mux_addr, byte i2c_adrr) : _sensor(i2c_adrr, -1)
{
    _mux_addr = mux_addr;
    _i2c_adrr = i2c_adrr;
}

bool Tsl::begin()
{
    Mux::select(_mux_addr);
    if (!_sensor.begin())
    {
        char err_msg[50];
        sprintf(err_msg, "TSL not detected at addr: %d/0x%02x", _mux_addr, _i2c_adrr);
        State::throwError(ErrorCode::sensor_init, err_msg);
    }
    _sensor.enableAutoRange(false);
    _sensor.setIntegrationTime(INTEGR_TIME);

    return true;
}

//TODO: error handling
float Tsl::read_lux()
{
    Mux::select(_mux_addr);
    _sensor.getEvent(&_event);

    val_lux = _event.light;

    return val_lux;
}