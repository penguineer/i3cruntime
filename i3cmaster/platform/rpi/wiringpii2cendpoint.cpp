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

#include "wiringpii2cendpoint.h"

#include <iostream>
#include <string>
#include <sstream>

#include <unistd.h>

#include <cstdlib>
#include <cerrno>

#include <wiringPiI2C.h>

using namespace i3c::sys::i2c;

namespace i3c {
namespace platform {
namespace rpi {

WiringPiI2CEndpoint::WiringPiI2CEndpoint(const I2CAddress address) throw (I2CEndpointException)
: I2CEndpoint(address)
{
  // get a handle for the I2C device
  const int fd = wiringPiI2CSetup(address);

  // check for error
  if (fd == -1) {
      throw I2CEndpointException(address, errno,
				  "Error on opening the I2C handle!");
  }

  // store fd
  m_fd = fd;
}

WiringPiI2CEndpoint::WiringPiI2CEndpoint(WiringPiI2CEndpoint&& other) throw ()
: I2CEndpoint(other.address()), m_fd(other.m_fd)
{
  other.m_fd = 0;
}

WiringPiI2CEndpoint::~WiringPiI2CEndpoint() throw()
{
  if (m_fd && (::close(m_fd) == -1))
    std::cerr << "Error on closing the I2C handle" << errno << std::endl;
}

#define I2C_EXC(MSG) \
    if (res < 0) { \
        throw I2CEndpointException(address(), errno, \
            (MSG)); \
    }

uint8_t WiringPiI2CEndpoint::read() throw ( I2CEndpointException )
{
  const int res = wiringPiI2CRead(m_fd);
  I2C_EXC("Error on simple I2C read!");
  return res;
}

uint16_t WiringPiI2CEndpoint::write ( const uint16_t data ) throw ( I2CEndpointException )
{
  const uint16_t res = wiringPiI2CWrite(m_fd, data);
  I2C_EXC("Error on simple I2C write!");
  return res;
}

uint16_t WiringPiI2CEndpoint::read_reg_8(const uint8_t reg) throw ( I2CEndpointException )
{
  const int res = wiringPiI2CReadReg8(m_fd, reg);
  I2C_EXC("Error on I2C 8-bit read!");
  return res;
}

uint16_t WiringPiI2CEndpoint::read_reg_16(const uint8_t reg) throw ( I2CEndpointException )
{
  const int res = wiringPiI2CReadReg16(m_fd, reg);
  I2C_EXC("Error on I2C 16-bit read!");
  return res;
}

uint16_t WiringPiI2CEndpoint::write_reg_8(const uint8_t reg, const uint8_t data) throw ( I2CEndpointException )
{
  const int res = wiringPiI2CWriteReg8(m_fd, reg, data);
  I2C_EXC("Error on I2C 8-bit write!");
  return res;
}

uint16_t WiringPiI2CEndpoint::write_reg_16(const uint8_t reg, const uint16_t data) throw ( I2CEndpointException )
{
  const int res = wiringPiI2CWriteReg16(m_fd, reg, data);
  I2C_EXC("Error on I2C 16-bit write!");
  return res;
}

} // namespace rpi
} // namespace platform
} // namespace i3c
