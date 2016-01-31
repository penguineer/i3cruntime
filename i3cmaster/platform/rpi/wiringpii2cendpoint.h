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

#pragma once

#include "../../sys/i2c/i2cendpoint.h"

using namespace i3c::sys::i2c;

namespace i3c {
namespace platform {
namespace rpi {

class WiringPiI2CEndpoint : public I2CEndpoint
{
public:
  //! Create an endpoint instance for a specific address.
  /*!
    * @param address The I2C address of the target device.
    * @throw I2CEndpointException if the endpoint cannot be initialized
    */
  WiringPiI2CEndpoint (const I2CAddress address) throw (I2CEndpointException);

  WiringPiI2CEndpoint (const WiringPiI2CEndpoint&) = delete;
  WiringPiI2CEndpoint& operator= (const WiringPiI2CEndpoint&) = delete;

  WiringPiI2CEndpoint(WiringPiI2CEndpoint&& other) throw ();

  virtual ~WiringPiI2CEndpoint() throw();

  //! Process an I2C request specified by a packet
  virtual I2CPacket&& process(const I2CPacket request) throw (I2CEndpointException);

private:
  int m_fd;
};

} // namespace rpi
} // namespace platform
} // namespace i3c
