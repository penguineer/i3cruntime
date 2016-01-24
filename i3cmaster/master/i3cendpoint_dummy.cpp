/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * This is the dummy implementation of the plattform-specific I2C endpoint part.
 */


#include "i3cendpoint.h"

#include <iostream>
#include <string>
#include <sstream>

namespace {
  
  void __dummy_message(const std::string msg) {
    std::cout << msg << std::endl;
  }
  
  int __dummy_input(const std::string msg) {
    std::cout << msg;
    
    int in;
    std::cin >> std::hex >> in;
    
    return in;
  }
  
} // anon namespace


namespace i3c {
 
} 