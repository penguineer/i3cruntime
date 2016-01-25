#include "operation.h"

namespace master {
namespace i3c {

Operation::Operation( uint8_t operation, std::vector<uint8_t> params) : operation(operation), m_data(params)
{


}

}
}
