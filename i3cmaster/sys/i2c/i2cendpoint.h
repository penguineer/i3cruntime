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



#ifndef I2CENDPOINT_H__
#define I2CENDPOINT_H__

#include <stdexcept>
#include <string>
#include <inttypes.h>
#include <map>
#include <vector>

// i2c includes
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "i2caddress.h"
#include "i2cendpointexception.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


namespace i2c
{


//! I2C communication endpoint
/*!
 * I2C endpoint representing a single device on the bus.
 *
 * An endpoint must be setup in order to be used. Afterwards read and write
 * operations can be arbitrarily used. On errors an I2CEndpointException is thrown.
 *
 * This design is strongly related to the wiringPi I2C library, but can be used for
 * other implementations, too.
 *
 * See http://wiringpi.com/reference/i2c-library/ for details. Most documentation
 * is just copied from there.
 */

class I2CEndpoint
{
public:


        //! Create an endpoint instance for a specific address.
        /*!
         * @param address The I2C address of the target device.
         * @throws std::out_of_range if the address is not a valid I2C address
         * @throw I2CEndpointException if the endpoint cannot be initialized
         */

        I2CEndpoint ( I2CAddress address ) throw ( I2CEndpointException );

        ~I2CEndpoint() throw();

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
        uint8_t read() throw ( I2CEndpointException );
        //! Simple device write.
        /*!
         * Some devices accept data this way without needing to access any internal registers.
         *
         * @param data The data to be written.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        uint8_t write ( const int data ) throw ( I2CEndpointException );

        //! Read 8 bits of data from a device register.
        /*!
         * @param reg The device register.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        uint8_t read_reg_8 ( const int reg ) throw ( I2CEndpointException );
        //! Read 16 bits of data from a device register.
        /*!
         * @param reg The device register.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        int read_reg_16 ( const int reg ) throw ( I2CEndpointException );

        //! Write 8 bits of data to a device register.
        /*!
         * @param reg The device register.
         * @param data The data.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        int write_reg_8 ( const int reg, const int data ) throw ( I2CEndpointException );
        //! Write 16 bits of data to a device register.
        /*!
         * @param reg The device register.
         * @param data The data.
         * @returns Result from the I2C call.
         * @throws I2CEndpointException if access to the I2C device fails.
         */
        int write_reg_16 ( const int reg, const int data ) throw ( I2CEndpointException );

protected:
        int _fd() const throw();
        I2CAddress m_address;
        int packetcounter;
        int m_fd;

private:
        // No Copies of this instance!
        // (Not implemented and never to be called.)
  I2CEndpoint ( const I2CEndpoint& other );

//         int count;
};
}
#endif
