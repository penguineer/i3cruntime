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

/*!
 * This is the dummy implementation of the plattform-specific I2C endpoint part.
 */


#include "i3cendpoint.h"

#include <iostream>
#include <string>
#include <sstream>

namespace {
  
  void __dummy_message(const std::string msg) {
    std::cout << msg << std::endl;
  }
  
  int __dummy_input(const std::string msg) {
    std::cout << msg;
    
    int in;
    std::cin >> std::hex >> in;
    
    return in;
  }
  
} // anon namespace


namespace i3c {
  
  I3CEndpoint::I3CEndpoint(i2c::I2CAddress address) throw (i2c::I2CEndpointException)
  {
    count=0;
    m_address = address;
    m_fd = 1;
    std::stringstream msg("");
    msg << "I2C dummy device " << m_address.to_int() << " has been set up with fd " << m_fd;
    
    ::__dummy_message(msg.str());    
  }
  
  I3CEndpoint::~I3CEndpoint() throw()
  {
    m_fd = 0;
    std::stringstream msg("");
    msg << "I2C dummy device " << m_address.to_int() << " has been closed.";
    
    ::__dummy_message(msg.str());
  }
  
  
//   i2c::I2CAddress I3CEndpoint::address() const throw()
//   {
//     return m_address;
//   }
//   
  int I3CEndpoint::_fd() const throw() {
    return m_fd;
  }
  
  
  uint8_t I3CEndpoint::read() throw(i2c::I2CEndpointException())
  {
    std::stringstream msg("");
    msg << "Please input simple read result (hex) for device 0x" << std::hex << m_address.to_int() << ": ";
    return ::__dummy_input(msg.str());
  }
  
  
  uint8_t I3CEndpoint::write(const uint8_t data) throw(i2c::I2CEndpointException)
  {
    std::stringstream msg("");
    msg << "Please input simple write result (hex) for device 0x" << std::hex << m_address.to_int()
    << ", written value 0x"  << data << ": ";
    return ::__dummy_input(msg.str());
    
  }
  /*
  uint8_t I3CEndpoint::read_reg_8(const int reg) throw(i2c::I2CEndpointException)
  {
    std::stringstream msg("");
    msg << "Please input 8-bit read result (hex) for device 0x" << std::hex << m_address
    << " on register 0x" << reg << ": ";
    return ::__dummy_input(msg.str());
  }
  
  int I2CEndpoint::read_reg_16(const int reg) throw(I2CEndpointException)
  {
    std::stringstream msg("");
    msg << "Please input 16-bit read result (hex) for device 0x" << std::hex << m_address
    << " on register 0x" << reg << ": ";
    return ::__dummy_input(msg.str());
  }*/
  /*
  int I2CEndpoint::write_reg_8(const int reg, const int data) throw(I2CEndpointException)
  {
    std::stringstream msg("");
    msg << "Please input 8-bit write result (hex) for device 0x" << std::hex << m_address
    << " on register 0x"  << reg << ", written value 0x" << data << ": ";
    return ::__dummy_input(msg.str());
  }*/
  
  
} // namespace xmppsc

// End of File
