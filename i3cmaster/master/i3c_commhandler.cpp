#include "i3c_commhandler.h"

namespace i3c {
uint8_t i3c_commhandler::i3c_send ( ::i2c::I2CAddress dst, uint8_t opcode, uint8_t* params, uint8_t par_count, uint8_t** response, uint8_t res_count )
{

}


void i3c_commhandler::scan_i2c_bus()
{
  int port, res;
// I2CAddress::Range::max
  /* Adressbereich 7 Bit */
  for (port = ::i2c::I2CAddress::Range::min;  port < i2c::I2CAddressRange::max; port++)
  {
    if (ioctl(device, I2C_SLAVE, port) < 0)
      perror("ioctl() I2C_SLAVE failed\n");
    else
    {
      /* kann gelesen werden? */
      res = i2c_smbus_read_byte(device);
      if (res >= 0)
	printf("i2c chip found at: %x, val = %d\n", port, res);
    }
  }
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
  uint8_t **response;
  
 // i3c_send ( dst,OP_STATUS, nullptr, 0, response, 1 );
  memcpy ( &status, response, sizeof ( status ) );
  return ( 0 );
}

}