#pragma once
#include "../api/i3c.h"
#include <string.h>
#include "../master/i3cpacket.h"

#include <stdio.h>

#include "i3cendpoint.h"
#include <sys/stat.h>
using namespace i3c::sys::i2c;

namespace i3c {
namespace master {


class i3c_commhandler
{


public:
        int init ( const char *i2cdevice );

        uint8_t i3c_getstatus (
                uint8_t dst,		// i²C-Adresse
                struct i3c_status status// return value: Status
        );

        uint8_t                         // Rückgabewert m. Fehlercode
        i3c_send (
                I2CAddress dst,            // I²C-Adresse
                uint8_t opcode,         // I3C-OpCode
                uint8_t *params,        // dazu passende Parameter
                uint8_t par_count,      // Anzahl der Parameterpakete
                uint8_t **response,     // Ziel-Array für die Antwort
                uint8_t res_count       // Anzahl der Antwortpakete
        );

private:
//   enum endpoint_priority priority;
        int devicedescriptor;
        char devicename[255];
        int packetcounter;
	// I3CEndpointBroker* epb;
        bool packet_isvalid ( I3CPacket p );
};


} // master
} // i3c