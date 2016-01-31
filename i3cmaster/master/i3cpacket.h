#pragma once

#include "../api/i3c.h"
#include <iostream>
#include <string>
#include <bitset>
#include <stdexcept>
#include "../sys/i2c/i2cpacket.h"

using namespace i3c::sys::i2c;

class I3CPacket
{
private:
        const uint8_t m_data;
        const I2CAddress m_destination;
        const enum packetcounter m_packetcount;
        const enum i3c_packet_state m_status;
        const uint8_t m_crc;
public:
	//! create I3CPacket from separate building blocks
        I3CPacket ( const uint8_t data,
		    const I2CAddress destination,
		    const enum packetcounter pc,
		    const enum i3c_packet_state st );

	// TODO is std::exception adequate here?
	//! Create an I3CPacket from 2 bytes serialized data that may have been transported over the i2c-bus.
	/**
	 * The metadata-byte is in the front.
	 * This will fail if the crc does not match.
	 */
        I3CPacket ( const I2CAddress source,
		    const uint16_t data ) throw (std::runtime_error);

	//! render this packet such that its contents are part of an i2c-packet
        I2CPacket render();

	//! for easy printing
        friend std::ostream& operator<< ( std::ostream &out, const I3CPacket &packet );


private:
        //! check if the package contains a valid crc
        bool isValidCRC () const;
	//! function to calculate the 5-bit-CRCsum of the packet
	uint8_t calc_crc() const;
	//! helper function to calculate the 5-bit CRCsum of one byte
        uint8_t CRC5x12 ( uint8_t crc, uint8_t data ) const;
        //! return the compiled metadata-byte for this packet
        uint8_t getMeta() const;
};


