
#include <stdint.h>
#include <stdbool.h>


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

/*
 * Error status codes if ST states ERROR.
 */
enum error {
	/* Abort
	 *
	 * Abbruch der Kommunikation, Verwerfen des aktuellen Frames
	 */
	E_ABORT = 0,

	/* CRC-Fehler
	 *
	 * das letzte Paket wird erneut verschickt
	 */
	E_CRC = 1,

	/* Frame Error
	 *
	 * Der Frame wird aufgrund von Paketverlust verworfen,
	 * Der Master startet die Übertragung des Frames erneut.
	 */
	E_FRAME = 2,

	/* Unbekannter OpCode
	 *
	 * Der OpCode wurde nicht erkannt.
	 */
	E_OPCODE =3,

	/* FIFO Overrun
	 *
	 * Der Befehlspuffer im Slave ist noch belegt, derzeit können
         * keine Pakete empfangen werden.
	 */
	E_FIFO = 4,

	/* No Packet Available
	 *
	 * (Antwort auf 2) Es liegt kein Paket zum Re-Send vor.
	 * Dieser Fehler tritt auf, wenn der Slave einen Reset
	 * durchgeführt hat und der Master die letzte Antwort nochmals
	 * anfordert.
	 */
	E_NOPACKET = 5,

	/*
	 * Additional error codes can be added here.
	 */
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
