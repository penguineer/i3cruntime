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
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>


namespace
{

void __dummy_message ( const std::string msg )
{
    std::cout << msg << std::endl;
}

int __dummy_input ( const std::string msg )
{
    std::cout << msg;

    int in;
    std::cin >> std::hex >> in;

    return in;
}
}

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


I2CEndpointException::I2CEndpointException ( I2CAddress address, const int error, const std::string& msg )
    : m_address ( address ), m_error ( error ), m_what ( msg ) { }

I2CEndpointException::~I2CEndpointException() throw() {}

I2CAddress I2CEndpointException::address() const throw()
{
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

I2CEndpoint* I2CEndpointBroker::endpoint ( I2CAddress address ) throw ( I2CEndpointException, std::out_of_range )
{
    // try to get endpoint from the map
    endpoint_map::iterator it = endpoints.find ( address );

    if ( it == endpoints.end() ) {
        // none found, create and setup
        I2CEndpoint* ep = new I2CEndpoint ( address );

        // store
        std::pair<endpoint_map::iterator, bool> res =
            endpoints.insert ( endpoint_map::value_type ( address, ep ) );

        // throw an exception if the endpoint could not be stored to the map
        if ( !res.second ) {
            delete ep;
            throw I2CEndpointException ( address, 0, "Could not store endpoint to broker!" );
        }

        return ep;
    }

    return it->second;
}

void I2CEndpointBroker::free_all_endpoints() throw()
{
    // close all endpoints
    for ( endpoint_map::iterator it = endpoints.begin(); it != endpoints.end(); it++ ) {
        I2CEndpoint* ep = it->second;
        delete ep;
        endpoints.erase ( it );
    }
}

/* Suche nach I2C-Adressen */
std::vector<I2CAddress>&& I2CEndpointBroker::scan_i2c_bus ( const char *bus ) const throw()
{
    std::vector<I2CAddress> addresses;

    int fd;
    unsigned long funcs;
    if ( ( fd = open ( bus, O_RDWR ) ) < 0 ) {
        perror ( "Failed to open the i2c bus\n" );
	// TODO throw an exception
    return std::move(addresses);
    }

    /* Abfragen, ob die I2C-Funktionen da sind */
    if ( ioctl ( fd ,I2C_FUNCS,&funcs ) < 0 ) {
        perror ( "ioctl() I2C_FUNCS failed" );
	// TODO throw an exception
    return std::move(addresses);
    }
    /* Ergebnis untersuchen */
    if ( funcs & I2C_FUNC_I2C ) {
        printf ( "I2C\n" );
    }
    if ( funcs & ( I2C_FUNC_SMBUS_BYTE ) ) {
        printf ( "I2C_FUNC_SMBUS_BYTE\n" );
    }

    /* scan bus and return addresses */


    uint8_t port, res;


    for ( port = (uint8_t)I2CAddress::Range::min; port < (uint8_t)I2CAddress::Range::max; port++ ) {
        if ( ioctl ( fd, I2C_SLAVE, port ) < 0 ) {
            perror ( "ioctl() I2C_SLAVE failed\n" );
        } else {
            /* kann gelesen werden? */
            res = i2c_smbus_read_byte ( fd );
            if ( res >= 0 ) {
                char error[1024];
                snprintf ( error, 1024, "i2c chip found at: %d value: %d" , port, res );
                perror ( error );

		addresses.push_back(res);
            }
        }

    }
    close ( fd );

    return std::move(addresses);
}

} // namespace xmppsc

// End of file