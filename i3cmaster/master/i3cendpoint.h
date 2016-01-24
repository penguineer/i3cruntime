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

#ifndef I3CENDPOINT_H__
#define I3CENDPOINT_H__

#include <stdexcept>
#include <string>
#include <inttypes.h>
#include <map>
#include "../sys/i2c/i2cendpoint.h"

enum endpoint_priority {
  LOW = 0,
  MEDIUM = 1,
  HIGH = 2,
  REALTIME = 3
};


namespace i3c
{
  
  
  //! I3C communication endpoint
  /*!
   * I3C endpoint representing a single device on the bus.
   *
   * This introduces an INT-Line in addition to device priorities
   */
  
  class I3CEndpoint  : public i2c::I2CEndpoint
  {
  public:
    
    
    //! Create an endpoint instance for a specific address.
    /*!
     * @param address The I2C address of the target device.
     * @throws std::out_of_range if the address is not a valid I2C address
     * @throw I2CEndpointException if the endpoint cannot be initialized
     */
    
    I3CEndpoint ( const i2c::I2CAddress address, enum endpoint_priority priority ) throw ( i2c::I2CEndpointException ) ;
    
    ~I3CEndpoint() throw();
    
    //! Return the address for this endpoint.
    /*!
     * @returns The endpoint device address.
     */
//     const i2c::I2CAddress address() const throw();
    
    //! Simple device read_reg_16
    /*!
     * Some devices present data when you read them without having to do any register transactions.
     *
     * @returns Result from the I2C call.
     * @throws i2c::I2CEndpointException if access to the I2C device fails.
     */
    uint8_t read() throw ( i2c::I2CEndpointException );
    //! Simple device write.
    /*!
     * Some devices accept data this way without needing to access any internal registers.
     *
     * @param data The data to be written.
     * @returns Result from the I2C call.
     * @throws I2CEndpointException if access to the I2C device fails.
     */
    uint8_t write ( const uint8_t data ) throw ( i2c::I2CEndpointException );
    
    //! Read 8 bits of data from a device register.
    /*!
     * @param reg The device register.
     * @returns Result from the I2C call.
     * @throws I2CEndpointException if access to the I2C device fails.
     */
     uint8_t read_reg_8 ( const int reg ) throw ( i2c::I2CEndpointException );

    //! Write 8 bits of data to a device register.
    /*!
     * @param reg The device register.
     * @param data The data.
     * @returns Result from the I2C call.
     * @throws I2CEndpointException if access to the I2C device fails.
     */
     int write_reg_8 ( const int reg, const int data ) throw ( i2c::I2CEndpointException );

  protected:
    int _fd() const throw();
//     const i2c::I2CAddress m_address;
//     int m_fd;
//     
  private:
    // No Copies of this instance!
    // (Not implemented and never to be called.)
    I3CEndpoint ( const I3CEndpoint& other );
    
    int count;
    int packetcounter;
    
//     const i2c::I2CAddress m_address;
//    int m_fd;
    
    // never to be called
    //! Write 16 bits of data to a device register.
    /*!
     * @param reg The device register.
     * @param data The data.
     * @returns Result from the I2C call.
     * @throws I2CEndpointException if access to the I2C device fails.
     */
         int write_reg_16 ( const int reg, const int data ) throw ( i2c::I2CEndpointException );
	
	 //! Read 16 bits of data from a device register.
	 /*!
	  * @param reg The device register.
	  * @returns Result from the I2C call.
	  * @throws I2CEndpointException if access to the I2C device fails.
	  */
	 int read_reg_16 ( const int reg ) throw ( i2c::I2CEndpointException );
	 
  };
//! this will implement i3c on top of i2c
class I3CEndpointBroker
{
public:
  //! Create an I3C broker instance.
  I3CEndpointBroker();
  
  //! Clean-up the instance and clean-up/remove all existing I2C endpoints.
  ~I3CEndpointBroker() throw();
  
  //! Create (if necessary) and return an I2C endpoint for the specified address.
  I3CEndpoint* endpoint ( i2c::I2CAddress address ) throw ( i2c::I2CEndpointException, std::out_of_range );
  
private:
  typedef std::map<i2c::I2CAddress, I3CEndpoint*> endpoint_map;
  endpoint_map endpoints;
  void free_all_endpoints() throw();
};
}
#endif