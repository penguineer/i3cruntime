#pragma once
#include "../api/i3c.h"
/*
 ** i3c Master-related structures
 **
 ** Author: Christof Schulze <christof.schulze@gmx.net>
 */

uint8_t                         // Rückgabewert m. Fehlercode
i3c_send (
        uint8_t dst,            // I²C-Adresse
        uint8_t opcode,         // I3C-OpCode
        uint8_t *params,         // dazu passende Parameter
        uint8_t par_count,      // Anzahl der Parameterpakete
        uint8_t **response,     // Ziel-Array für die Antwort
        uint8_t res_count       // Anzahl der Antwortpakete
);


uint8_t i3c_getstatus (
        uint8_t dst,
        struct i3c_status status
);
