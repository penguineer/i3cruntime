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

public:
        void create ( uint8_t data, uint8_t destination, int pc, enum i3c_packet_state st );
};



