#pragma once

#include "../../sys/i2c/i2cendpoint.h"

using namespace i3c::sys::i2c;

namespace i3c {
namespace platform {
namespace dummy {

class DummyI2CEndpoint : public I2CEndpoint
{
    DummyI2CEndpoint(const I2CAddress address) throw(I2CEndpointException);

    virtual ~DummyI2CEndpoint();

    virtual uint8_t read() throw (I2CEndpointException);

    virtual uint16_t write ( const uint16_t data ) throw ( I2CEndpointException );

    virtual uint16_t read_reg_8 ( const uint8_t reg ) throw ( I2CEndpointException );

    virtual uint16_t read_reg_16 ( const uint8_t reg ) throw ( I2CEndpointException );

    virtual uint16_t write_reg_8 ( const uint8_t reg, const uint8_t data ) throw ( I2CEndpointException );

    virtual uint16_t write_reg_16 ( const uint8_t reg, const uint16_t data ) throw ( I2CEndpointException );

};

} // dummy
} // platform
} // i3c
