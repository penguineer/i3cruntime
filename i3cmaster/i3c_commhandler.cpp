#include "i3c_commhandler.h"

uint8_t i3c_commhandler::i3c_send ( uint8_t dst, uint8_t opcode, uint8_t* params, uint8_t par_count, uint8_t** response, uint8_t res_count )
{

}

int i3c_commhandler::init(const char *i2cdevice) {
  int fd;
  unsigned long funcs;
  
  if ( ( fd = open ( i2cdevice, O_RDWR ) ) < 0 ) {
    perror ( "Failed to open the i2c bus\n" );
    return ( 1 );
  }

  /* Abfragen, ob die I2C-Funktionen da sind */
  if ( ioctl ( fd ,I2C_FUNCS,&funcs ) < 0 ) {
    perror ( "ioctl() I2C_FUNCS failed" );
    return ( 1 );
  }
  /* Ergebnis untersuchen */
  if ( funcs & I2C_FUNC_I2C ) {
    printf ( "I2C\n" );
  }
  if ( funcs & ( I2C_FUNC_SMBUS_BYTE ) ) {
    printf ( "I2C_FUNC_SMBUS_BYTE\n" );
  }
  
  this->devicedescriptor = fd;
  this->packetcounter = 0;
  memcpy(this->devicename,i2cdevice,sizeof(i2cdevice));
  /* scan bus and create list of slaves */
  scan_i2c_bus (); 
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

/* Suche nach I2C-Adressen */
void i3c_commhandler::scan_i2c_bus ()
{
  int device = this->devicedescriptor;
  int port, res;
  
  /* Adressbereich 7 Bit */
  for ( port = 0; port < 127; port++ ) {
    if ( ioctl ( device, I2C_SLAVE, port ) < 0 ) {
      perror ( "ioctl() I2C_SLAVE failed\n" );
    } else {
      /* kann gelesen werden? */
      res = i2c_smbus_read_byte ( device );
      if ( res >= 0 ) {
	printf ( "i2c chip found at: %x, val = %d\n", port, res );
      }
    }
  }
}