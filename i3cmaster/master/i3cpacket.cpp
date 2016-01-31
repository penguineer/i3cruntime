#include "i3cpacket.h"

using namespace i3c::sys::i2c;

I3CPacket::I3CPacket ( uint8_t data, uint8_t destination, enum packetcounter pc, i3c_packet_state st ) : destination ( destination ), status ( st ), data ( data ), packetcount ( pc )
{
  uint8_t meta = (((this->packetcount )<<2) | this->status) <<5;
  uint8_t crc = 0;
  crc = CRC5x12 ( crc, destination );
  crc = CRC5x12 ( crc, data );
  crc = CRC5x12 ( crc, meta );
  crc >>3;
  this->crc = crc;
}

uint8_t I3CPacket::getMeta()
{
    uint8_t meta = 0x00;
    meta =  this->packetcount;
    meta = meta <<2;
    meta = meta | this->status;
    meta = meta <<5;
    meta = meta | ( this->crc);
    return meta;
}


I3CPacket::I3CPacket ( uint16_t data ) throw ( std::exception )
{
    uint8_t tdata;
    uint8_t meta;

    meta = ( uint8_t ) ( ( data & 0xFF00 ) >> 8 );
    this->data= ( uint8_t ) ( data & 0x00FF );
    this->packetcount = static_cast<packetcounter> ( meta >>7 );
    this->status = static_cast<i3c_packet_state> ( ( meta & 0x60 ) >> 5 );
    this->crc = ( meta & 0x1f );

    // TODO should the members be set to 0 if an exception is raised?
    if (!isvalid())
      throw std::exception();

}

bool I3CPacket::isvalid()
{
  uint8_t meta = (getMeta() & 0xE0 );
  uint8_t crc = 0;
  crc = CRC5x12 ( crc, destination );
  crc = CRC5x12 ( crc, data );
  crc = CRC5x12 ( crc, meta );
  crc >>3;
  return (crc == this->crc);
}


i3c::sys::i2c::I2CPacket I3CPacket::render()
{
    uint16_t i2cdata;
    i2cdata = getMeta();
    i2cdata <<8;
    i2cdata = i2cdata | this->data;
    I2CPacket i2cpacket ( this->packetcount, this->destination,i2cdata );

    return i2cpacket;
}


std::ostream& operator<< ( std::ostream &out, I3CPacket &packet )
{
    std::bitset<8> bdest ( packet.destination );
    std::bitset<8> bmeta ( packet.getMeta() );
    std::bitset<8> bdata ( packet.data );
    out << "[ destination: " << std::hex << unsigned ( packet.destination )  << "(" << bdest << ") metadata: "  << unsigned ( packet.getMeta() ) <<
        " (" << bmeta << ") data: " << unsigned ( packet.data ) << "(" << bdata  << ") ]" << std::endl;
    return out;
}
/**
 * Calculate a 5-bit CRC based on the generator polynom 0x12 (see definition of POLYNOMIAL).
 *
 * The result is in the first 5 bits of the returned byte and must be shifted for final evaluation!
 *
 * http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
 *
 * Initial: 0x00
 * 	I3C check messages always start with an I2C-address, which is never 0
 */
uint8_t I3CPacket::CRC5x12 ( uint8_t const crc, uint8_t const data )
{
    uint8_t remainder = crc;

    remainder ^= data;

    for ( uint8_t bit = 8; bit; bit-- ) {
        // if uppermost bit is '1'
        if ( remainder & 0x80 ) {
            remainder = remainder ^ POLYNOMIAL;
        }

        // next bit
        remainder <<= 1;
    }

    return remainder;
}


/*

PC            1 bit
PC ist ein Packet Counter im aktuellen Frame, der bei jedem Paket
negiert wird. Der Initialwert ist
0: wenn es im Frame keine Parameter-Pakete gibt
1: wenn im Frame Parameter-Pakete übertragen werden

ST            2 bits
Als Zahl kodierter Status, einer der folgenden:

0) ACK
Es sind keine Fehler aufgetreten.
1) START (nur Master)
Das Paket mit diesem Status leitet einen neuen Frame ein.
Die Payload enthält den OpCode.
2) FIN
Wird gesetzt, wenn die Parameter (vom Master zum Slave) oder die
Antwort (vom Slave zum Master) vollständig gesetzt sind.
3) ERROR
Es kam zu einem Problem bei der Datenübertragung.
Die Payload enthält einen detaillierten Fehlerstatus
(siehe ERROR-Byte).

CRC           5 bits
Eine 5-bittige Checksumme über 24 bit, wobei die CRC-Bit bei
der Berechnung auf 000 gesetzt werden. Die 24 Bit bestehen aus:
- der 7-bit-I2C-Adresse mit angehängter '0' als Padding
- der Payload
- dem Header

Das Generatorpolynom ist 0x12 (0x25) gemäß
http://users.ece.cmu.edu/~koopman/crc/.

*/
