#include "i3cpacket.h"

using namespace i3c::sys::i2c;

I3CPacket::I3CPacket ( const uint8_t data,
		       const I2CAddress destination,
		       const enum packetcounter pc,
		       const i3c_packet_state st )
: m_data ( data ),
  m_destination ( destination ),
  m_packetcount ( pc ),
  m_status ( st ),
  m_crc ( calc_crc() )
{
}

uint8_t I3CPacket::getMeta() const
{
    uint8_t meta = m_packetcount;
    meta <<= 2;
    meta |= m_status;
    meta <<= 5;
    meta |= m_crc;

    return meta;
}

#include <sstream>


I3CPacket::I3CPacket ( const I2CAddress source, const uint16_t data ) throw ( std::runtime_error )
: m_data( (uint8_t)( data & 0x00FF ) ),
  m_destination(source),
  m_packetcount( static_cast<packetcounter>(data>> 15) ),
  m_status( static_cast<i3c_packet_state>((data & 0x6000) >> 13)),
  m_crc( (data & 0x1f00) >>8 )
{
    // TODO should the members be set to 0 if an exception is raised?
    // Tux: I would not raise the exception here. isValid tells if the packet is fine.
    if (!isValidCRC())
    {
      std::stringstream ss;
      ss << this << "calculated crc: " << calc_crc();
      throw std::runtime_error(std::string("CRC from the input value does not match the data: ") + ss.str());
    }
}

uint8_t I3CPacket::calc_crc() const
{
  uint8_t crc = 0;

  crc = CRC5x12 ( crc, m_destination );
  crc = CRC5x12 ( crc, m_data );
  crc = CRC5x12 ( crc, getMeta() & 0xE0 );
  crc >>= 3;

  return crc;
}

bool I3CPacket::isValidCRC() const
{
  return calc_crc() == m_crc;
}


i3c::sys::i2c::I2CPacket I3CPacket::render()
{
    uint16_t i2cdata;
    i2cdata = getMeta();
    i2cdata <<= 8;
    i2cdata |=  m_data;
    // TODO this may not be the best sequence number
    I2CPacket i2cpacket ( m_packetcount, m_destination, I2COperation::WRITE_SIMPLE, i2cdata );

    return i2cpacket;
}

/**
  * See http://users.ece.cmu.edu/~koopman/crc/ for details.
  *
  * The CRC polynomial is
  * 	0x12 => x^5 + x^2 + 1
  * 	which is 0x25 in explicit +1 notation,
  * 	then moved to the beginning of the byte
  */
#define POLYNOMIAL (0x25 << 2)

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
uint8_t I3CPacket::CRC5x12 ( uint8_t const crc, uint8_t const data ) const
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


std::ostream& operator<< ( std::ostream &out, const I3CPacket &packet )
{
    std::bitset<8> bdest ( packet.m_destination );
    std::bitset<8> bmeta ( packet.getMeta() );
    std::bitset<8> bdata ( packet.m_data );
    out << "[ destination: " << std::hex << unsigned ( packet.m_destination )  << "(" << bdest << ") metadata: "  << unsigned ( packet.getMeta() ) <<
        " (" << bmeta << ") data: " << unsigned ( packet.m_data ) << "(" << bdata  << ") ]" << std::endl;
    return out;
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
