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


#include "i2cpacket.h"

namespace i3c {
namespace sys {
namespace i2c {

I2CPacket::I2CPacket(const uint16_t seqNo,
		     const I2CAddress peer,
	             const uint16_t data) throw()
: m_seqNo(seqNo), m_peer(peer), m_data(data)
{}

I2CPacket::I2CPacket(const I2CPacket &other) throw()
: m_seqNo(other.m_seqNo), m_peer(other.m_peer), m_data(other.m_data)
{}

const uint16_t I2CPacket::seqNo() const throw()
{
  return m_seqNo;
}

const I2CAddress I2CPacket::peer() const throw()
{
  return m_peer;
}

const uint16_t I2CPacket::data() const throw()
{
  return m_data;
}

} // namespace i2c
} // namespace sys
} // namespace i3c
