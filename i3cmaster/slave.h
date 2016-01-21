#include <stdint.h>

class Slave {
private:
  int count;
  int priority;
  uint8_t address;
  int packetcounter;
  
public:
  void init();
  void set_address(uint8_t address);
  
};