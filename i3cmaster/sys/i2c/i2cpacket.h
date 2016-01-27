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

#include <cstdint>

#include "i2caddress.h"

namespace i3c {
namespace sys {
namespace i2c {

//! Packet plus meta-data for I2C communication
class I2CPacket
{
public:
  //! Create a new packet from values.
  I2CPacket(const uint16_t seqNo,
	    const I2CAddress peer,
	    const uint16_t data) throw();

  //! Copy an existing packet
  I2CPacket(const I2CPacket &other) throw();

  //! The sequence number will be copied to the answer packet
  const uint16_t seqNo() const throw();

  //! The communication peer, i.e. the slave address.
  const I2CAddress peer() const throw();

  //! The 16 bit data sent over the I2C bus.
  const uint16_t data() const throw();

private:
  const uint16_t m_seqNo;
  const I2CAddress m_peer;
  const uint16_t m_data;
};

} // namespace i2c
} // namespace sys
} // namespace i3c