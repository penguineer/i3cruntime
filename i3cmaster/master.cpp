/*
** i3c Master-Implementation
**
** Author: Christof Schulze <christof.schulze@gmx.net>
*/

#include <iostream> 
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "i3c_master.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "slavelist.h"

//#include <../crc/crc.h>

uint8_t crc ( uint8_t data, uint8_t meta )
{
        // TODO FIXME
        return 0x0b;
}

struct packet create_packet ( uint8_t data, uint8_t destination, enum packetcounter pc, enum i3c_packet_state st )
{
        struct packet p;
        p.data=data;
        p.status=st;
        p.pc=pc;
        p.destination = destination;
        return p;
}

uint8_t assemble_meta ( struct packet p )
{
        uint8_t meta = 0x00;
        meta =  p.pc;
        meta = meta <<2;
        meta = meta | p.status;
        meta = meta <<5;
        meta = meta | ( 0x1F & crc ( p.data,meta ) );
        return meta;
}
void assemble_packet ( struct packet p, uint8_t *assembled )
{
        // printf("meta: %llx\n", meta);
        assembled[0] = p.data;
        assembled[1] = assemble_meta ( p );
}

uint8_t                         // Rückgabewert m. Fehlercode
i3c_send (
        uint8_t dst,            // I²C-Adresse
        uint8_t opcode,         // I3C-OpCode
        uint8_t *params,        // dazu passende Parameter
        uint8_t par_count,      // Anzahl der Parameterpakete
        uint8_t **response,     // Ziel-Array für die Antwort
        uint8_t res_count       // Anzahl der Antwortpakete
)
{

}
uint8_t i3c_getstatus (
        uint8_t dst,		// i²C-Adresse
        struct i3c_status status// return value: Status
)
{
        uint8_t *nullptr;
        uint8_t **response;

        i3c_send ( dst,OP_STATUS, nullptr, 0, response, 1 );
        memcpy ( &status, response, sizeof ( status ) );
        return ( 0 );
}

struct slavelistitem slavelisti;


/* Suche nach I2C-Adressen */
void scan_i2c_bus ( int device )
{
        int port, res;

        /* Adressbereich 7 Bit */
        for ( port = 0; port < 127; port++ ) {
                if ( ioctl ( device, I2C_SLAVE, port ) < 0 ) {
                        perror ( "ioctl() I2C_SLAVE failed\n" );
                } else {
                        /* kann gelesen werden? */
                        res = i2c_smbus_read_byte ( device );
                        if ( res >= 0 ) {
                                printf ( "i2c chip found at: %x, val = %d\n", port, res );
                        }            
                }
        }
}

int main()
{
        const char i2cbus[255]="/dev/i2c-1";
        uint8_t address;
        unsigned long funcs;
        int fd;

        if ( ( fd = open ( i2cbus, O_RDWR ) ) < 0 ) {
                perror ( "Failed to open the i2c bus\n" );
                exit ( 1 );
        }

        /* Abfragen, ob die I2C-Funktionen da sind */
        if ( ioctl ( fd ,I2C_FUNCS,&funcs ) < 0 ) {
                perror ( "ioctl() I2C_FUNCS failed" );
                exit ( 1 );
        }
        /* Ergebnis untersuchen */
        if ( funcs & I2C_FUNC_I2C ) {
                printf ( "I2C\n" );
        }
        if ( funcs & ( I2C_FUNC_SMBUS_BYTE ) ) {
                printf ( "I2C_FUNC_SMBUS_BYTE\n" );
        }

        /* und Bus abscannen */
        scan_i2c_bus ( fd );


        /* Spezifizieren der Slave-Adresse -> Kommunikation frei geben */
        if ( ioctl ( fd, I2C_SLAVE, address ) < 0 ) {
                perror ( "Failed to acquire bus access and/or talk to slave\n" );
                exit ( 1 );
        }

        uint8_t wire[2];
        assemble_packet ( create_packet ( 0xfe, 0x34, ODD, ST_START), wire );
        printf ( "wire: %02x %02x \n", wire[0], wire[1] );

}

