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

#include "../../sys/i2c/i2cendpointbroker.h"

#include <map>
#include <mutex>

using namespace i3c::sys::i2c;

namespace i3c {
namespace platform {
namespace rpi {

class WiringPiI2CEndpointBroker : public I2CEndpointBroker
{
public:
  WiringPiI2CEndpointBroker();

  //! Create (if necessary) and return an I2C endpoint for the specified address.
  virtual std::shared_ptr<I2CEndpoint> endpoint (const I2CAddress address) throw (I2CEndpointException);

  virtual std::vector<I2CAddress>&& scan() throw (I2CEndpointException);

private:
  typedef std::map<I2CAddress, std::shared_ptr<I2CEndpoint> > EndpointsMap;
  EndpointsMap m_endpoints;
  std::mutex m_endpoints_mutex;
};

} // namespace rpi
} // namespace platform
} // namespace i3c
