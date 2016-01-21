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
 * This is the wiringPi implementation of the plattform-specific I2C
 * endpoint part.
 */


#include "i2cendpoint.h"

#include <iostream>
#include <string>
#include <sstream>

#include <unistd.h>

#include <cstdlib>
#include <cerrno>

#include <wiringPiI2C.h>

namespace xmppsc {

I2CEndpoint::I2CEndpoint(const int address) throw (I2CEndpointException, std::out_of_range)
    : m_address(address), m_fd(0)
{
    if (address < 0 || address > 0xff) {
        std::stringstream msg("");
        msg << "I2C address " << address << " is out of range, must be between 0 and 0xFF!";
        throw std::out_of_range(msg.str());
    }

    // get handle for the I2C device
    const int fd = wiringPiI2CSetup(m_address);

    // check for error
    if (fd == -1) {
        throw I2CEndpointException(m_address, errno,
                                   "Error on opening the I2C handle!");
    }

    // store fd
    m_fd = fd;
}

I2CEndpoint::~I2CEndpoint() throw()
{
    if (::close(m_fd) == -1)
        std::cerr << "Error on closing the I2C handle" << errno << std::endl;
}

const int I2CEndpoint::address() const throw()
{
    return m_address;
}

int I2CEndpoint::_fd() const throw() {
    return m_fd;
}

#define I2C_EXC(MSG) \
    if (res < 0) { \
        throw I2CEndpointException(m_address, errno, \
            (MSG)); \
    } \
 
int I2CEndpoint::read() throw(I2CEndpointException)
{
    const int res = wiringPiI2CRead(m_fd);
    I2C_EXC("Error on simple I2C read!");
    return res;
}


int I2CEndpoint::write(const int data) throw(I2CEndpointException)
{
    const int res = wiringPiI2CWrite(m_fd, data);
    I2C_EXC("Error on simple I2C write!");
    return res;
}

int I2CEndpoint::read_reg_8(const int reg) throw(I2CEndpointException)
{
    const int res = wiringPiI2CReadReg8(m_fd, reg);
    I2C_EXC("Error on I2C 8-bit read!");
    return res;
}

int I2CEndpoint::read_reg_16(const int reg) throw(I2CEndpointException)
{
    const int res = wiringPiI2CReadReg16(m_fd, reg);
    I2C_EXC("Error on I2C 16-bit read!");
    return res;
}

int I2CEndpoint::write_reg_8(const int reg, const int data) throw(I2CEndpointException)
{
    const int res = wiringPiI2CWriteReg8(m_fd, reg, data);
    I2C_EXC("Error on I2C 8-bit write!");
    return res;
}

int I2CEndpoint::write_reg_16(const int reg, const int data) throw(I2CEndpointException)
{
    const int res = wiringPiI2CWriteReg16(m_fd, reg, data);
    I2C_EXC("Error on I2C 16-bit write!");
    return res;
}

} // namespace xmppsc

// End of File
