#include "../sys/i2c/i2cendpoint.h"
#include "i3cendpoint.h"

namespace master {
namespace i3c {
//! this will implement i3c on top of i2c
class I3CEndpointBroker
{
public:
  //! Create an I3C broker instance.
  I3CEndpointBroker();
  
  //! Clean-up the instance and clean-up/remove all existing I2C endpoints.
  ~I3CEndpointBroker() throw();
  
  //! Create (if necessary) and return an I2C endpoint for the specified address.
  I3CEndpoint* endpoint ( i2c::I2CEndpoint ) throw ( i2c::I2CEndpointException, std::out_of_range );
  
private:
  typedef std::map<i2c::I2CAddress, I3CEndpoint*> endpoint_map;
  endpoint_map endpoints;
  void free_all_endpoints() throw();
};
}
}