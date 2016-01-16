/*
** i3c Master-Implementation 
**
** Author: Christof Schulze <christof.schulze@gmx.net>
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "i3c.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//#include <../crc/crc.h>

uint8_t crc(uint8_t data, uint8_t meta) {
	// TODO FIXME
	return 0x0b;
}

struct packet create_packet(uint8_t data, uint8_t destination, enum packetcounter pc, enum packet_state st)
{
	struct packet p;
	p.data=data;
	p.status=st;
	p.pc=pc;
	p.destination = destination;
	return p;
}

uint8_t assemble_meta(struct packet p){
	uint8_t meta = 0x00;
	meta =  p.pc;
	meta = meta <<2;
	meta = meta | p.status;
	meta = meta <<5;
	meta = meta | (0x1F & crc(p.data,meta));
	return meta;
}
void assemble_packet(struct packet p, uint8_t *assembled){
	// printf("meta: %llx\n", meta);
	assembled[0] = p.data;
	assembled[1] = assemble_meta(p);
}

int main()
{
i2cbus=1;	
int fd;

/* Device oeffen */
//if ((fd = open(expander.I2CBus, O_RDWR)) < 0)
if ((fd = open(i2cbus, O_RDWR)) < 0)
  {
  perror("Failed to open the i2c bus\n");
  exit(1);
  }

/* Spezifizieren der Slave-Adresse -> Kommunikation frei geben */
if (ioctl(fd, I2C_SLAVE, address) < 0)
  {
  perror("Failed to acquire bus access and/or talk to slave\n");
  exit(1);
  }


	uint8_t wire[2];
	assemble_packet(create_packet(0xfe, 0x34, ODD, 8), wire);
	printf("wire: %02x %02x \n", wire[0], wire[1]);

}

