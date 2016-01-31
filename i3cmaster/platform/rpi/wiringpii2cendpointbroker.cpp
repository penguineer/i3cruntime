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

#include "wiringpii2cendpointbroker.h"

#include "wiringpii2cendpoint.h"

// These includes are for bus scanning
#include <iostream>
#include <cerrno>
#include <sys/ioctl.h>
#include <unistd.h>

#include <wiringPiI2C.h>


using namespace i3c::sys::i2c;

namespace i3c {
namespace platform {
namespace rpi {


WiringPiI2CEndpointBroker::WiringPiI2CEndpointBroker()
{}

std::shared_ptr< I2CEndpoint > WiringPiI2CEndpointBroker::endpoint(const I2CAddress address) throw (I2CEndpointException)
{
  // try to get endpoint from cache
  EndpointsMap::iterator it( m_endpoints.find(address) );

  // not found?
  if (it == m_endpoints.end()) {
    // create an endpoint
    const std::shared_ptr<I2CEndpoint> endpoint( std::make_shared<WiringPiI2CEndpoint>(address) );

    const std::pair<I2CAddress, std::shared_ptr<I2CEndpoint> > pair(address, endpoint);

    const std::pair<EndpointsMap::iterator, bool> res ( m_endpoints.insert( pair ) );

    if (!res.second)
      throw I2CEndpointException(address, 0, "Cannot insert endpoint into cache map!");

    it = res.first;
  }

  return it->second;
}

/*
 * The following define comes from linux/i2c-dev.h, but is copied here to save us an include
 * and the dependency to the packet libi2c-dev.
 */

/* NOTE: Slave address is 7 or 10 bits, but 10-bit addresses
 * are NOT supported! (due to code brokenness)
 */
#define I2C_SLAVE	0x0703	/* Use this slave address */


std::vector< I2CAddress >&& WiringPiI2CEndpointBroker::scan() throw (I2CEndpointException)
{
  //TODO it would be sooo nice if this came from WiringPi …

  // get a device from Wiring Pi. We'll set the slave address later, but the bus
  // is correct, saves us the RPi management stuff.
  const int device = wiringPiI2CSetup(0);

  // check for error
  if (device == -1)
      throw I2CEndpointException(0, errno,
				  "Error on opening the I2C bus!");

  std::vector<I2CAddress> slaves;

  for (uint8_t port = (uint8_t)I2CAddress::Range::min;
       port < (uint8_t)I2CAddress::Range::max;
       port++) {
    if (ioctl(device, I2C_SLAVE, port) < 0)
      throw I2CEndpointException(I2CAddress(port), errno, "ioctl() I2C_SLAVE failed");
    else {
      // try to read device
      uint8_t res = wiringPiI2CRead(device);

      // if successful, add to slaves list
      if (res >= 0)
	slaves.push_back(I2CAddress(res));
    }
  }

  // close the bus
  ::close(device);

  return std::move(slaves);
}


} // namespace rpi
} // namespace platform
} // namespace i3c
