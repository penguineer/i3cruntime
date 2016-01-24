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

uint8_t I3CEndpoint::read ( const int reg ) throw ( i2c::I2CEndpointException )
{
// TODO implementieren
}

uint8_t I3CEndpoint::write ( const uint8_t operation, const uint8_t *data, uint8_t len ) throw ( i2c::I2CEndpointException )
{
// TODO implementieren

    // 1. paket aus den daten bauen
    // 2. paket an den endpoint via i2c übertragen
    uint16_t pdata;
    pdata = operation;
    pdata <<8;
    pdata = pdata | data;

    m_endpoint->write ( pdata );
}


// I3CEndpoint::I3CEndpoint ( const I3CEndpoint& other )
// {
//   // TODO implementieren
// this->m_bus_priority = other.m_bus_priority;
// this->m_i2c_endpoint = other.m_i2c_endpoint;
// }

// TODO use packetcounter enum
I3CEndpoint::I3CEndpoint ( i2c::I2CAddress address, enum endpoint_priority priority ) throw ( i2c::I2CEndpointException )
: m_endpoint ( std::move ( i2c::I2CEndpoint ( address ) ) ),
m_count ( 0 ),m_packetcounter ( 0 ) ,
m_bus_priority ( priority )
{
    // TODO implementieren
// //   m_i2c_endpoint = i
}


}
}
