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

#include <stdexcept>
#include <cstdint>

#include "i2caddress.h"

namespace i3c {
namespace sys {
namespace i2c {

//! I2C bus operations
enum class I2COperation {
  //! Simple device read_16
  READ_SIMPLE = 0,
  //! Simple device write_16
  WRITE_SIMPLE,
  //! Read 8 bits of data from a device register.
  READ_REG_8,
  //! Read 16 bits of data from a device register.
  READ_REG_16,
  //! Write 8 bits of data to a device register.
  WRITE_REG_8,
  //! Write 16 bits of data to a device register.
  WRITE_REG_16
};

//! Packet plus meta-data for I2C communication
class I2CPacket
{
public:
  //! Create a new packet from values without register.
  /**
   * Only valid for ops READ_SIMPLE and WRITE_SIMPLE
   */
  I2CPacket(const uint16_t seqNo,
	    const I2CAddress peer,
	    const I2COperation op,
	    const uint16_t data) throw(std::invalid_argument);

  //! Create a new packet from values with register.
  /**
   * Not valid for ops READ_SIMPLE and WRITE_SIMPLE
   */
  I2CPacket(const uint16_t seqNo,
	    const I2CAddress peer,
	    const I2COperation op,
	    const uint8_t reg,
	    const uint16_t data) throw(std::invalid_argument);

  //! Create a response packet
  I2CPacket(const I2CPacket &other,
	    const uint16_t data) throw();

  //! Copy an existing packet
  I2CPacket(const I2CPacket &other) throw();

  //! The sequence number will be copied to the answer packet
  const uint16_t seqNo() const throw();

  //! The communication peer, i.e. the slave address.
  const I2CAddress peer() const throw();

  //! The operation
  const I2COperation op() const throw();

  //! The register
  const uint8_t reg() const throw();

  //! The 16 bit data sent over the I2C bus.
  const uint16_t data() const throw();

private:
  const uint16_t m_seqNo;
  const I2CAddress m_peer;
  const I2COperation m_op;
  const uint8_t m_reg;
  const uint16_t m_data;
};

} // namespace i2c
} // namespace sys
} // namespace i3c