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

#include "i2caddress.h"
#include "i2cendpointexception.h"

namespace i3c {
namespace sys {
namespace i2c {

//TODO check read/write return types!

class I2CEndpoint
{
public:
        //! Create an endpoint instance for a specific address.
        /*!
         * @param address The I2C address of the target device.
         * @throw I2CEndpointException if the endpoint cannot be initialized
         */
        I2CEndpoint (const I2CAddress address) throw (I2CEndpointException);

        virtual ~I2CEndpoint() throw();

        //! Return the address for this endpoint.
        /*!
         * @returns The endpoint device address.
         */
        const I2CAddress address() const throw();

        //! Simple device read_reg_16
        /*!
         * Some devices present data when you read them without having to do any register transactions.
         *
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        virtual uint8_t read() throw (I2CEndpointException) = 0;

	//! Simple device write.
        /*!
         * Some devices accept data this way without needing to access any internal registers.
         *
         * @param data The data to be written.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        virtual uint16_t write ( const uint16_t data ) throw ( I2CEndpointException ) = 0;

        //! Read 8 bits of data from a device register.
        /*!
         * @param reg The device register.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        virtual uint16_t read_reg_8 ( const uint8_t reg ) throw ( I2CEndpointException ) = 0;

	//! Read 16 bits of data from a device register.
        /*!
         * @param reg The device register.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        virtual uint16_t read_reg_16 ( const uint8_t reg ) throw ( I2CEndpointException ) = 0;

        //! Write 8 bits of data to a device register.
        /*!
         * @param reg The device register.
         * @param data The data.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
	virtual uint16_t write_reg_8 ( const uint8_t reg, const uint8_t data ) throw ( I2CEndpointException ) = 0;

	//! Write 16 bits of data to a device register.
        /*!
         * @param reg The device register.
         * @param data The data.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        virtual uint16_t write_reg_16 ( const uint8_t reg, const uint16_t data ) throw ( I2CEndpointException ) = 0;

private:
        I2CAddress m_address;
};


} // namespace i2c
} // namespace sys
} // namespace i3c
