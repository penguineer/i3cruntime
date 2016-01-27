
#ifndef I3COPERATION_H__
#define I3COPERATION_H__

#include <inttypes.h>
#include <vector>

namespace master { namespace i3c {
class Operation {
public:
  enum class i3c_operation {
    RESET = 1,  //     Reset: reboot the slave
    STATUS = 2, //    obtain status from slave
    RREAD = 3,  //    read register
    RWRITE = 4, //    write register
    FWMGMT = 5, //    start firmware update - management frame
    FWDATA = 6, //    Firmware update data:
    RDDESC = 7, //    read device Descriptor
    SETADR = 8, //    set i2c address
    SDDESC = 9  //    set Device-Descriptor (except I2C-Address)
    // 10-15  RESERVIERT
  };
  Operation(uint8_t operation, std::vector<uint8_t> params) ;
private:
  const uint8_t operation;
  const std::vector<uint8_t> m_data;
};
}
}
#endif