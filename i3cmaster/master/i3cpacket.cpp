#include "i3cpacket.h"

void i3cpacket::create ( uint8_t data, uint8_t destination, enum packetcounter pc, i3c_packet_state st )
{
    uint8_t meta = 0x00;
    meta =  pc;
    meta = meta <<2;
    meta = meta | st;
    meta = meta <<5;

    uint8_t crc = 0;
    crc = CRC5x12 ( crc, destination );
    crc = CRC5x12 ( crc, data );
    crc = CRC5x12 ( crc, meta );

    meta = meta | ( crc >>3 );
    this->meta = meta;
    this->destination = destination;
    this->status = st;
    this->data = data;
    this->packetcount = pc;

}
#include <stdio.h>
// #include "../debug.h"
#include <string>
#include <string.h>
#include <iostream>
#include <bitset>
void i3cpacket::interpret ( uint16_t data )
{
    // TODO implement me
//     this->data = data;
//     uint8_t meta = metadata;
//     uint8_t pc =  (uint8_t) (0x00000001 & metadata);
//     // TODO find a way to deal with uint8_i enum class packetcounter conversion gracefully. This also must be supported by C
//     // this->packetcount = pc;
//     uint8_t st = (uint8_t)(0x00000110 & metadata) >>1;
//    // TODO find a way to deal with uint8_T to i3c_status conversion
//     // this->status = (i3c_status)st;
//     crc = (uint8_t)(0x00011111 & metadata);
}

i3c::sys::i2c::I2CPacket i3cpacket::render()
{
    i3c::sys::i2c::I2CPacket i2cpacket;
    uint16_t i2cdata;
    i2cdata = this->meta;
    i2cdata <<8;
    i2cdata = i2cdata | this->data;
    i2cpacket = new i3c::sys::i2c::I2CPacket ( this->packetcount, this->destination,i2cdata );
    return i2cpacket;
}

std::ostream& operator<< ( std::ostream &out, i3cpacket &packet )
{
    std::bitset<8> bdest ( packet.destination );
    std::bitset<8> bmeta ( packet.meta );
    std::bitset<8> bdata ( packet.data );
    out << "[ destination: " << std::hex << unsigned ( packet.destination )  << "(" << bdest << ") metadata: "  << unsigned ( packet.meta ) <<
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
uint8_t i3cpacket::CRC5x12 ( uint8_t const crc, uint8_t const data )
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
