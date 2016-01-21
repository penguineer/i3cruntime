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

//TODO comments

#include "i2cendpoint.h"


namespace xmppsc {


I2CEndpointException::I2CEndpointException(const uint8_t address, const int error, const std::string& msg)
    : m_address(address), m_error(error), m_what(msg) { }

I2CEndpointException::~I2CEndpointException() throw() {}

const uint8_t I2CEndpointException::address() const throw() {
    return m_address;
}

const int I2CEndpointException::error() const throw()
{
    return m_error;
}

const char* I2CEndpointException::what() const throw()
{
    return m_what.c_str();
}




I2CEndpointBroker::I2CEndpointBroker()
    : endpoints()
{

}

I2CEndpointBroker::~I2CEndpointBroker() throw()
{
    free_all_endpoints();
}

I2CEndpoint* I2CEndpointBroker::endpoint(const uint8_t address, enum endpoint_priority priority) throw(I2CEndpointException, std::out_of_range)
{
    // try to get endpoint from the map
    endpoint_map::iterator it = endpoints.find(address);

    if (it == endpoints.end()) {
        // none found, create and setup
        I2CEndpoint* ep = new I2CEndpoint(address, priority);

        // store
        std::pair<endpoint_map::iterator, bool> res =
            endpoints.insert(endpoint_map::value_type(address, ep));

        // throw an exception if the endpoint could not be stored to the map
        if (!res.second) {
            delete ep;
            throw I2CEndpointException(address, 0, "Could not store endpoint to broker!");
        }

        return ep;
    }

    return it->second;
}

void I2CEndpointBroker::free_all_endpoints() throw()
{
    // close all endpoints
    for (endpoint_map::iterator it = endpoints.begin(); it != endpoints.end(); it++) {
        I2CEndpoint* ep = it->second;
        delete ep;
        endpoints.erase(it);
    }
}


} // namespace xmppsc

// End of file
