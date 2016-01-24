#pragma once

#include <stdexcept>
#include <string>

#include "i2caddress.h"

namespace i3c {
namespace sys {
namespace i2c {


//! Exception during I2C communication via an endpoint.
class I2CEndpointException : public std::exception
{
public:
        //! Create a new exception.
        /*!
         * @param address Device address of the I2C peer.
         * @param errno The errno from the backing I2C library
         * @param const msg an error message if available
         */
        I2CEndpointException (const I2CAddress address, const int error, const std::string& msg);

        virtual ~I2CEndpointException() throw();

        //! Get the device address corresponding to this exception.
        virtual const I2CAddress address() const throw();

        //! Get the error (errno) corresponding to this exception.
        virtual const int error() const throw();

        //! Get the exception message.
        /*!
         * \returns the exception message
         */
        virtual const char* what() const throw();

private:
        const I2CAddress m_address;
        const int m_error ;
        const std::string m_what;
};

} // namespace i2c
} // namespace sys
} // namespace i3c
