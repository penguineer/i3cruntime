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



#include <string>
#include <sstream>

#include "i2caddress.h"



namespace i3c {
namespace sys {
namespace i2c {


I2CAddress::I2CAddress ( const uint8_t address ) throw ( std::out_of_range )
  : m_address(address)
{
  /*
   * Check Range and throw exception accordingly
   */
  range_check(address);
}

I2CAddress::I2CAddress(const i2c::I2CAddress& i2c_address) throw ()
  : m_address(i2c_address.m_address)
{
  /*
   * Range check is not necessary when taking address from an already established instance.
   */
}

I2CAddress::I2CAddress(const I2CAddress&& i2c_address) throw ()
  : m_address(std::move(i2c_address.m_address))
{
  /*
   * Range check is not necessary when taking address from an already established instance.
   */
}


bool I2CAddress::operator < ( const I2CAddress i2caddress ) const
{
    return m_address < i2caddress.m_address;
}

I2CAddress::operator uint8_t()  const
{
  return this->m_address;
}

void I2CAddress::range_check(const uint8_t address) throw (std::out_of_range)
{
  /*
   * Check Range and throw exception accordingly
   */
  if ( ( address < (uint8_t)Range::min ) || ( address > (uint8_t)Range::max ) ) {
    std::stringstream msg ( "" );
    msg << "I2C address " << address << " is out of range, must be between 0 and 127!";
    throw std::out_of_range ( msg.str() );
  }
}

} // namespace i2c
} // namespace sys
} // namespace i3c
