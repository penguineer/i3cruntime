#include "slave.h"


void Slave::set_address(uint8_t address) {
    this->address = address;
  }

void Slave::init()
{
  this->packetcounter=0;
}
