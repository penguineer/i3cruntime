
#ifndef I3COPERATION_H__
#define I3COPERATION_H__

#include <inttypes.h>
#include <vector>

namespace master { namespace i3c {
class Operation {
public:
  Operation(uint8_t operation, std::vector<uint8_t> params) ;
private:
  const uint8_t operation;
  const std::vector<uint8_t> m_data;

};
}
}
#endif