#pragma once
#include <stdint.h>
#include "../api/i3c.h"

class packet
{
private:
        uint8_t data;
        uint8_t meta;
        uint8_t destination;
        enum i3c_packet_state status;

        // the communication handler keeps track of the packet counter and therefore must calculate and check the crc. 
	// This allows interleaved communication.

        uint8_t  crc ( uint8_t data, uint8_t meta );
public:
        void create ( uint8_t data, uint8_t destination, int pc, enum i3c_packet_state st );
};



