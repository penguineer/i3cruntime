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
#include "i2cendpoint.h"

#include <stdexcept>
#include <memory>
#include <vector>

namespace i3c {
namespace sys {
namespace i2c {

//! Store and manage a cache of already established I2C endpoints
class I2CEndpointBroker
{
public:
        //! Clean-up the instance and clean-up/remove all existing I2C endpoints.
        virtual ~I2CEndpointBroker() throw();

        //! Create (if necessary) and return an I2C endpoint for the specified address.
        virtual std::shared_ptr<I2CEndpoint> endpoint (const I2CAddress address) throw (I2CEndpointException) = 0;

	virtual std::vector<I2CAddress>&& scan() throw (I2CEndpointException) = 0;
};

} // namespace i2c
} // namespace sys
} // namespace i3c
