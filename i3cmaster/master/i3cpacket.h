#pragma once

#include "../api/i3c.h"
#include <iostream>
#include <string>
#include <bitset>

#include "../sys/i2c/i2cpacket.h"

using namespace i3c::sys::i2c;
class I3CPacket
{

        /**
         * See http://users.ece.cmu.edu/~koopman/crc/ for details.
         *
         * The CRC polynomial is
         * 	0x12 => x^5 + x^2 + 1
         * 	which is 0x25 in explicit +1 notation,
         * 	then moved to the beginning of the byte
         */
#define POLYNOMIAL (0x25 << 2)

private:
        uint8_t data;
        uint8_t destination;
        enum packetcounter packetcount;
        enum i3c_packet_state status;
        uint8_t crc;
public:

	//! create I3CPacket from separate building blocks
        I3CPacket ( uint8_t data, uint8_t destination, enum packetcounter pc, enum i3c_packet_state st );

	// TODO is std::exception adequate here?
	//! create an I3CPacket from 2 bytes serialized data that may have been transported over the i2c-bus. The metadata-byte is in the front. This will fail if the crc does not match.
        I3CPacket ( uint16_t data ) throw (std::exception);

	//! render this packet such that its contents are part of an i2c-packet
        I2CPacket render();


	//! for easy printing
        friend std::ostream& operator<< ( std::ostream &out, I3CPacket &packet );


private:
        //! check if the package contains a valid crc
        bool isvalid ();
	//! calculate the 5-bit CRCsum
        uint8_t CRC5x12 ( uint8_t crc, uint8_t data );#
        //! return the compiled metadata-byte for this packet
        uint8_t getMeta();
};


