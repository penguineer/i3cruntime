/* ----------------------------------------------------------------------------
   libconfig - A library for processing structured configuration files
   Copyright (C) 2005-2010  Mark A Lindner

   This file is part of libconfig.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, see
   <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------------
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include <stdint.h>
using namespace std;
using namespace libconfig;

  enum class endpoint_priority  {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2,
    REALTIME = 3
  };
// This example reads the configuration file 'example.cfg' and displays
// some of its contents.

endpoint_priority stringToEnum(string input) throw (std::runtime_error) {
if (input.compare("REALTIME") == 0)
		return endpoint_priority::REALTIME;
if (input.compare("HIGH") == 0)
		return endpoint_priority::HIGH;
if (input.compare("MEDIUM") == 0 )
		return endpoint_priority::MEDIUM;
if (input.compare("LOW") == 0 )
	return endpoint_priority::LOW;

throw(std::runtime_error("parsing error in config-file, could not parse buspriority. Use one of REALTIME, HIGH, MEDIUM, LOW"));
}

int main(int argc, char **argv)
{
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
    cout << "Bus name: " << name << endl << endl;
  }
  catch(const SettingNotFoundException &nfex)
  {
    cerr << "No 'name' setting in configuration file." << endl;
  }

  const Setting& root = cfg.getRoot();

  // Output a list of all i3c in the endpoints.
  try
  {
    const Setting &i3c = root["endpoints"]["i3c"];
    int count = i3c.getLength();

    cout << setw(30) << left << "NAME" << "  "
         << setw(10) << left << "ADDRESS" << "   "
         << setw(6) << left << "PRIO" << "  "
         << endl;

    for(int i = 0; i < count; ++i)
    {
      const Setting &i3ce = i3c[i];

      // Only output the record if all of the expected fields are present.
      string name ;
//      uint8_t address;
	int address;
      string prio;
enum endpoint_priority eprio;
      if(!(i3ce.lookupValue("name", name)
           && i3ce.lookupValue("address", address)
           && i3ce.lookupValue("buspriority", prio)
           ))
        continue;
	eprio = stringToEnum(prio);
      cout << setw(30) << left << name << "  "
           << setw(10) << left << address << "  "
           << setw(6) << left << unsigned(eprio) << "  "
           << endl;
    }
    cout << endl;
  }
  catch(const SettingNotFoundException &nfex)
  {
    // Ignore.
  }

  // Output a list of all i3c in the endpoints.
  try
  {
    const Setting &i2c = root["endpoints"]["i2c"];
    int count = i2c.getLength();

    cout << setw(30) << left << "NAME" << "  "
         << setw(10) << left << "ADDRESS" << "   "
         << setw(6) << left << "PRIO" << "  "
         << endl;

    for(int i = 0; i < count; ++i)
    {
      const Setting &i2ce = i2c[i];

      // Only output the record if all of the expected fields are present.
      string name, media;
      string prio;
      int address;

      if(!(i2ce.lookupValue("name", name)
           && i2ce.lookupValue("buspriority", prio)
           && i2ce.lookupValue("address", address)
           ))
        continue;

      cout << setw(30) << left << name << "  "
           << setw(10) << left << address << "  "
           << setw(6) << left << prio << "  "
           << endl;
    }
    cout << endl;
  }
  catch(const SettingNotFoundException &nfex)
  {
    // Ignore.
  }

  return(EXIT_SUCCESS);
}

// eof
