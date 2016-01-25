#include "../sys/i2c/i2cendpoint.h"
#include "i3cendpoint.h"
#include <vector>

using namespace i3c::sys::i2c;

namespace master {
namespace i3c {
//! this will implement i3c on top of i2c
class I3CEndpointBroker
{
  public:
    //! Clean-up the instance and clean-up/remove all existing I2C endpoints.
    virtual ~I3CEndpointBroker() throw();

    //! Create (if necessary) and return an I2C endpoint for the specified address.
    virtual std::shared_ptr<I3CEndpoint> endpoint (const I2CAddress address) throw (I2CEndpointException) = 0;

//     virtual std::vector<I2CAddress>&& scan() throw (I2CEndpointException) = 0;
//   };



  //! Create an I3C broker instance.
//   I3CEndpointBroker();
  
  //! Clean-up the instance and clean-up/remove all existing I2C endpoints.
//   ~I3CEndpointBroker() throw();
  
  //! Create (if necessary) and return an I2C endpoint for the specified address.
//   I3CEndpoint* endpoint ( i2c::I2CEndpoint ) throw ( i2c::I2CEndpointException, std::out_of_range );
  
// private:
//   typedef std::vector<I2CAddress, I3CEndpoint> endpoint_map;
//   endpoint_map endpoints;
//   void free_all_endpoints() throw();
};
}
}