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



#ifndef __I2CENDPOINTBROKER_H
#define __I2CENDPOINTBROKER_H

#include "i2cendpoint.h"

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

namespace i2c
{
  //! Store and manage a cache of already established I2C endpoints
  class I2CEndpointBroker
  {
  public:
    //! Create an I2C broker instance.
    I2CEndpointBroker();

    //! Clean-up the instance and clean-up/remove all existing I2C endpoints.
    ~I2CEndpointBroker() throw();

    //! Create (if necessary) and return an I2C endpoint for the specified address.
    I2CEndpoint* endpoint ( I2CAddress address ) throw ( I2CEndpointException, std::out_of_range );

  private:
    typedef std::map<I2CAddress, I2CEndpoint*> endpoint_map;
    endpoint_map endpoints;
    std::vector< I2CAddress >&& scan_i2c_bus ( const char* bus ) const throw();
    void free_all_endpoints() throw();
  };
}

#endif
