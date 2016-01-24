#include "i2cendpointexception.h"

namespace i2c {

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



}