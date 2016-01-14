struct slave {
	uint8_t address[255];
};

enum status { 
	ACK = 0,
	START = 1,
	FIN = 2,
	ERROR = 3
};
enum packetcounter {
	EVEN = 0, 
	ODD = 1
};

struct packet  {
	uint8_t data;
	enum status status;	
	enum packetcounter pc;
	uint8_t crc;
	uint8_t adr;
	uint8_t destination;
} ;

struct frame {
	// amount of packets inside frame
	int length;
	struct packet *packets;
} ;

enum error {
	E_ABORT = 0,
	E_CRC = 1,
	E_FRAME = 2,
	E_OPCODE =3,
	E_FIFO = 4
};

enum statusbyte {
	ST_ACK = 0,
	ST_DATA = 1,
	ST_BACKOFF=2
};

enum opcode {
	OP_RESET = 0,
	OP_STATUS = 1,
	OP_READ_REGISTER = 2,
	OP_WRITE_REGISTER =3,
	OP_FIRMWARE_MGMT = 4,
	OP_FIRMWARE_DATA = 5,
	OP_RESERVED1 = 6,
	OP_RESERVED2 = 7,
	OP_RESERVED3 = 8,
	OP_RESERVED4 = 9,
	OP_RESERVED5 = 10,
	OP_RESERVED6 = 11,
	OP_RESERVED7 = 12,
	OP_RESERVED8 = 13,
	OP_RESERVED9 = 14,
	OP_RESERVED0 = 15,
};

/*
   1	0001
   2	0010
   3	0011
   4	0100
   5	0101
   6	0110
   7	0111
   8	1000
   9	1001
   A	1010
   B	1011
   C	1100
   D	1101
   E	1110
   F	1111

*/
