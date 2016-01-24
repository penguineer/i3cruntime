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
#include <stdexcept>

namespace i3c {
namespace sys {
namespace i2c {

//! Representation of an address on the i2c bus
class I2CAddress
{
public:
    //! the range in which I2CAddress-addresses are valid
    enum class Range {
        min = 0, max = 127
    };

    //! create an I2CAddress
    /*!
     * @param address Device address of the I2C peer.
     */
    I2CAddress(const uint8_t address) throw ( std::out_of_range );

    I2CAddress(const I2CAddress& i2c_address) throw ();

    I2CAddress(const I2CAddress&& i2c_address) throw ();

    /*
     * Assignment operator is not viable with immutable classes. Use the copy constructor.
     */
    I2CAddress& operator= (I2CAddress arg) = delete;

    //! return an uint8_t Representation of the object
    operator uint8_t() const;

    bool operator < ( const I2CAddress i2caddress ) const ;

private:
    //! Check the range of an address value and throw std::out_of_range if not within Range.
    void range_check(const uint8_t address) throw (std::out_of_range);

private:
    //! the i2c address
    const uint8_t m_address;
};


} // namespace i2c
} // namespace sys
} // namespace i3c
