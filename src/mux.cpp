#include "mux.h"
#include "state.h"

namespace Mux
{
    void select(byte i) {
        if (i > 7)
        {
            State::throwError(ErrorCode::generic, "Bad Mux addres: " + i);
        }
        
        Wire.beginTransmission(MUX_I2C_ADDR);
        Wire.write(1 << i);
        Wire.endTransmission();  
    }
}