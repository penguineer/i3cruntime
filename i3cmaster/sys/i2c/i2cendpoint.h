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
#include "i2cpacket.h"

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

	//! Process an I2C request specified by a packet
	/**
          * @param request The request packet.
          * @returns Result from the I2C call.
          * @throws I2CEndpointException if access to the I2C device fails.
	  */
	virtual I2CPacket&& process(const I2CPacket request) throw (I2CEndpointException) = 0;
private:
        I2CAddress m_address;
};


} // namespace i2c
} // namespace sys
} // namespace i3c
