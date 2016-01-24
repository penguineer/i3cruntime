#include "packet.h"

void packet::create ( uint8_t data, uint8_t destination, int pc, i3c_packet_state st )
{
  uint8_t meta = 0x00;
  meta =  pc;
  meta = meta <<2;
  meta = meta | st;
  meta = meta <<5;
  meta = meta | ( 0x1F & crc ( data,meta ) );
  this->meta = meta;
  this->destination = destination;
  this->status = st;
}