/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * This is the dummy implementation of the plattform-specific I2C endpoint part.
 */

#include "i2cendpoint_dummy.h"

#include "../../sys/i2c/i2cendpoint.h"
#include "../../sys/i2c/i2cendpointexception.h"

#include <iostream>
#include <string>
#include <sstream>

namespace {

void __dummy_message(const std::string msg) {
    std::cout << msg << std::endl;
}

int __dummy_input(const std::string msg) {
    std::cout << msg;

    int in;
    std::cin >> std::hex >> in;

    return in;
}

} // anon namespace


namespace i3c {
namespace platform {
namespace dummy {

DummyI2CEndpoint::DummyI2CEndpoint(const sys::i2c::I2CAddress address) throw(I2CEndpointException)
  : I2CEndpoint(address)
{
    std::stringstream msg("");
    msg << "I2C dummy device " << address << " has been set up.";

    ::__dummy_message(msg.str());
}

DummyI2CEndpoint::~DummyI2CEndpoint()
{
    std::stringstream msg("");
    msg << "I2C dummy device " << address() << " has been closed.";

    ::__dummy_message(msg.str());
}

uint8_t DummyI2CEndpoint::read() throw ( I2CEndpointException )
{
    std::stringstream msg("");
    msg << "Please input simple read result (hex) for device 0x" << std::hex << address() << ": ";
    return ::__dummy_input(msg.str());
}

uint16_t DummyI2CEndpoint::write(const uint16_t data) throw ( I2CEndpointException )
{
    std::stringstream msg("");
    msg << "Please input simple write result (hex) for device 0x" << std::hex << address()
        << ", written value 0x"  << data << ": ";
    return ::__dummy_input(msg.str());
}

uint16_t DummyI2CEndpoint::read_reg_8(const uint8_t reg) throw ( I2CEndpointException )
{
    std::stringstream msg("");
    msg << "Please input 8-bit read result (hex) for device 0x" << std::hex << address()
        << " on register 0x" << reg << ": ";
    return ::__dummy_input(msg.str());
}

uint16_t DummyI2CEndpoint::read_reg_16(const uint8_t reg) throw ( I2CEndpointException )
{
    std::stringstream msg("");
    msg << "Please input 16-bit read result (hex) for device 0x" << std::hex << address()
        << " on register 0x" << reg << ": ";
    return ::__dummy_input(msg.str());
}

uint16_t DummyI2CEndpoint::write_reg_8(const uint8_t reg, const uint8_t data) throw ( I2CEndpointException )
{
    std::stringstream msg("");
    msg << "Please input 8-bit write result (hex) for device 0x" << std::hex << address()
        << " on register 0x"  << reg << ", written value 0x" << data << ": ";
    return ::__dummy_input(msg.str());
}

uint16_t DummyI2CEndpoint::write_reg_16(const uint8_t reg, const uint16_t data) throw ( I2CEndpointException )
{
    std::stringstream msg("");
    uint8_t temp = address();
    msg << "Please input 16-bit write result (hex) for device 0x" << std::hex << temp
        << " on register 0x" << reg << ", written value 0x" << data << ": ";
    return ::__dummy_input(msg.str());
}


} // dummy
} // platform
} // i3c

// End of File
