
#ifndef DEBUG_H
#define DEBUG_H

#include<iostream>



#define DBGVAR( os, var ) \
(os) << "DBG: " << __FILE__ << "(" << __LINE__ << ") "\
 << #var << " = [" << (var) << "]" << std::endl

#define DBGMSG( os, msg ) \
(os) << "DBG: " << __FILE__ << "(" << __LINE__ << ") " \
<< msg << std::endl

const char *hextobin(uint8_t input);
#endif