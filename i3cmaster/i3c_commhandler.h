#pragma once
#include "i3c.h"
#include <string.h>
#include "packet.h"
#include "slavelist.h"
#include <fcntl.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include <sys/stat.h>

class i3c_commhandler
{
private:
        int devicedescriptor;
        char devicename[255];
        int packetcounter;
	Slavelist slaves;
	
	bool packet_isvalid(packet p);
	int scan_i2c_bus();

public:
        int init ( const char *i2cdevice );

        uint8_t i3c_getstatus (
                uint8_t dst,		// i²C-Adresse
                struct i3c_status status// return value: Status
        );

        uint8_t                         // Rückgabewert m. Fehlercode
        i3c_send (
                uint8_t dst,            // I²C-Adresse
                uint8_t opcode,         // I3C-OpCode
                uint8_t *params,        // dazu passende Parameter
                uint8_t par_count,      // Anzahl der Parameterpakete
                uint8_t **response,     // Ziel-Array für die Antwort
                uint8_t res_count       // Anzahl der Antwortpakete
        );
};
