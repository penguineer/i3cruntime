#include "packet.h"


// TODO - move this where it belongs
uint8_t packet::crc ( uint8_t data, uint8_t meta )
{
  // TODO FIXME
  return 0x0b;
}

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

/*
void assemble_packet ( struct packet p, uint8_t *assembled )
{
  // printf("meta: %llx\n", meta);
  assembled[0] = p.data;
  assembled[1] = assemble_meta ( p );
}
*/
