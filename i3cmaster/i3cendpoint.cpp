#include "i3cendpoint.h"


namespace i3c
{
  
I3CEndpointBroker::I3CEndpointBroker()
    : endpoints()
{

}

I3CEndpointBroker::~I3CEndpointBroker() throw()
{
    free_all_endpoints();
}

I3CEndpoint* I3CEndpointBroker::endpoint ( i2c::I2CAddress address ) throw ( i2c::I2CEndpointException, std::out_of_range )
{
    // try to get endpoint from the map
    endpoint_map::iterator it = endpoints.find ( address );

    if ( it == endpoints.end() ) {
        // none found, create and setup
        I3CEndpoint* ep = new I3CEndpoint ( address );

        // store
        std::pair<endpoint_map::iterator, bool> res =
            endpoints.insert ( endpoint_map::value_type ( address, ep ) );

        // throw an exception if the endpoint could not be stored to the map
        if ( !res.second ) {
            delete ep;
            throw i2c::I2CEndpointException ( address, 0, "Could not store endpoint to broker!" );
        }

        return ep;
    }

    return it->second;
}

void I3CEndpointBroker::free_all_endpoints() throw()
{
    // close all endpoints
    for ( endpoint_map::iterator it = endpoints.begin(); it != endpoints.end(); it++ ) {
        I3CEndpoint* ep = it->second;
        delete ep;
        endpoints.erase ( it );
    }
}

}
