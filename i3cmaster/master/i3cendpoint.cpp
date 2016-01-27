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



#include "i3cendpoint.h"
#include "packet.h"
namespace master
{
namespace i3c
{
// I3CEndpoint::I3CEndpoint ( const I3CEndpoint& other ) : I3CEndpoint()
// {
//
// }

uint8_t I3CEndpoint::read ( const int reg ) throw ( I2CEndpointException )
{
// TODO implementieren
}

uint8_t I3CEndpoint::write ( Operation operation ) throw ( I2CEndpointException )
{
// TODO implementieren

    // 1. paket aus den daten bauen
    // 2. paket an den endpoint via i2c übertragen

}


// I3CEndpoint::I3CEndpoint ( const I3CEndpoint& other )
// {
//   // TODO implementieren
// this->m_bus_priority atu= other.m_bus_priority;
// this->m_i2c_endpoint = other.m_i2c_endpoint;
// }

// TODO use packetcounter enum
I3CEndpoint::I3CEndpoint ( I2CAddress address, enum endpoint_priority priority ) throw ( I2CEndpointException )
: m_address(

address),
m_count ( 0 ),m_packetcounter ( 0 ) ,
m_bus_priority ( priority )
{
    // TODO implementieren
// //   m_i2c_endpoint = i
}


}
}
