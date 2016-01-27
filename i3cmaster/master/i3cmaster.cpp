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

#include <unistd.h>


#include <string.h>

#include <iostream>
// #include "slave.h"
// #include "i3c_commhandler.h"

using namespace std;

int main()
{
    const char i2cbus[255]="/dev/i2c-1";
    uint8_t address;
std::cout << "yeah!" << endl;
//     i3c::i3c_commhandler ch;
//     ch.init ( i2cbus );
// TODO i2c entfernen.
// TODO i2server-socket zum abgeben der Daten nutzen.


 }

