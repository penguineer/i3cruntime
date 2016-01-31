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
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace libconfig;


int main()
{
    // TODO config file klasse suchen und das file lesen.

    const char i2cbus[255]="/dev/i2c-1";
    uint8_t address;
    const char configfile[255]="example.config";
    std::cout << "yeah!" << endl;
    // TODO - socket öffnen um Daten entgegen zu nehmen. Diese Daten per i2c über den Bus schicken.
// TODO initialize the i2c-bus,


    uint8_t destination = 0x21;
    uint8_t data = 0xaa;
    I3CPacket p( data ,destination, ODD, ST_START );

    cout << p << endl;

    Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
      cfg.readFile("example.cfg");
    }
    catch(const FileIOException &fioex)
    {
      std::cerr << "I/O error while reading file." << std::endl;
      return(EXIT_FAILURE);
    }
    catch(const ParseException &pex)
    {
      std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
      << " - " << pex.getError() << std::endl;
      return(EXIT_FAILURE);
    }

    // Get the store name.
    try
    {
      string name = cfg.lookup("name");
      cout << "Store name: " << name << endl << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'name' setting in configuration file." << endl;
    }

    const Setting& root = cfg.getRoot();

    // Output a list of all books in the inventory.
    try
    {
      const Setting &books = root["inventory"]["books"];
      int count = books.getLength();

      cout << setw(30) << left << "TITLE" << "  "
      << setw(30) << left << "AUTHOR" << "   "
      << setw(6) << left << "PRICE" << "  "
      << "QTY"
      << endl;

      for(int i = 0; i < count; ++i)
      {
	const Setting &book = books[i];

	// Only output the record if all of the expected fields are present.
	string title, author;
	double price;
	int qty;

	if(!(book.lookupValue("title", title)
	  && book.lookupValue("author", author)
	  && book.lookupValue("price", price)
	  && book.lookupValue("qty", qty)))
	  continue;

	cout << setw(30) << left << title << "  "
	<< setw(30) << left << author << "  "
	<< '$' << setw(6) << right << price << "  "
	<< qty
	<< endl;
      }
      cout << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      // Ignore.
    }

    // Output a list of all books in the inventory.
    try
    {
      const Setting &movies = root["inventory"]["movies"];
      int count = movies.getLength();

      cout << setw(30) << left << "TITLE" << "  "
      << setw(10) << left << "MEDIA" << "   "
      << setw(6) << left << "PRICE" << "  "
      << "QTY"
      << endl;

      for(int i = 0; i < count; ++i)
      {
	const Setting &movie = movies[i];

	// Only output the record if all of the expected fields are present.
	string title, media;
	double price;
	int qty;

	if(!(movie.lookupValue("title", title)
	  && movie.lookupValue("media", media)
	  && movie.lookupValue("price", price)
	  && movie.lookupValue("qty", qty)))
	  continue;

	cout << setw(30) << left << title << "  "
	<< setw(10) << left << media << "  "
	<< '$' << setw(6) << right << price << "  "
	<< qty
	<< endl;
      }
      cout << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      // Ignore.
    }

    return(EXIT_SUCCESS);


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
