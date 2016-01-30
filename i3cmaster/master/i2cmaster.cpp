/*
 * * i3c Master-Implementation
 **
 ** Author: Christof Schulze <christof.schulze@gmx.net>
 */

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "i3c_master.h"

#include <unistd.h>


#include <string.h>

#include <iostream>
// #include "slave.h"
// #include "i3c_commhandler.h"

#include "i3cpacket.h"


#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include "operation.h"
#include "../api/i3c.h"

#include <libconfig.h++>

using namespace std;



template<typename T> void print_queue ( T& q )
{
    while ( !q.empty() ) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

#include "../debug.h"

int main()
{
    // TODO config file klasse suchen und das file lesen.

    const char i2cbus[255]="/dev/i2c-1";
    uint8_t address;
    const char configfile[255]="example.config";
    std::cout << "yeah!" << endl;
    // TODO - socket öffnen um Daten entgegen zu nehmen. Diese Daten per i2c über den Bus schicken.
// TODO initialize the i2c-bus,

    i3cpacket p;
    uint8_t destination = 0x21;
    uint8_t data = 0xaa;
    p.create ( data ,destination, ODD, ST_START );

    cout << p << endl;
//  //   printf ( "%s\n", result);
//     std::priority_queue<int> q;
//
//     for ( int n : {
//                 1,8,5,6,3,4,0,9,3,2
//             } )
//         q.push ( n );
//
//     print_queue ( q );
//
//
//
//     std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
//
//     for ( int n : {
//                 1,8,5,6,3,4,0,9,3,2
//             } )
//         q2.push ( n );
//
//     print_queue ( q2 );
}
