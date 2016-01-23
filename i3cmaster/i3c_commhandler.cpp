#include "i3c_commhandler.h"
namespace i3c {
uint8_t i3c_commhandler::i3c_send ( i2c::I2CAddress dst, uint8_t opcode, uint8_t* params, uint8_t par_count, uint8_t** response, uint8_t res_count )
{

}

int i3c_commhandler::init(const char *i2cdevice) {
  int fd;

  epb = new I3CEndpointBroker();
 
}

uint8_t i3c_getstatus (
  uint8_t dst,		// i²C-Adresse
  struct i3c_status status// return value: Status
)
{
  uint8_t *nullptr;
  uint8_t **response;
  
  // i3c_send ( dst,OP_STATUS, nullptr, 0, response, 1 );
  memcpy ( &status, response, sizeof ( status ) );
  return ( 0 );
}

}