cmake_minimum_required(VERSION 2.8.9)

project (I3CMASTER CXX)

set(CMAKE_CXX_FLAGS "-std=c++14")

### Check the I2C library

# do we have wiringPi?
find_library(WIRINGPI_LIBRARY NAMES wiringPi wiringPiDev)
if (WIRINGPI_LIBRARY)
  # add the wiring pi files
  set(WIRINGPI_FILES
      platform/rpi/wiringpii2cendpoint.cpp
      platform/rpi/wiringpii2cendpointbroker.cpp
  )
endif(WIRINGPI_LIBRARY)

# do we have libconfig++ ?
find_library(CONFIG_LIBRARIES NAMES config++)
find_library(CONFIG_LIBRARIES NAMES pthread)

add_executable(i3cmaster
debug.cpp
master/i3cmaster.cpp
platform/dummy/i2cendpoint_dummy.cpp
master/i3cpacket.cpp
sys/i2c/i2cpacket.cpp
sys/i2c/i2caddress.cpp
sys/i2c/i2cendpoint.cpp
sys/i2c/i2cdispatcher.cpp
sys/i2c/i2cendpointexception.cpp
master/i3cendpoint.cpp
sys/i2c/i2cendpointbroker.cpp
#master/i3c_commhandler.cpp
master/operation.cpp
${WIRINGPI_FILES}
)

add_executable(i2cmaster
# debug.cpp
master/i2cmaster.cpp
platform/dummy/i2cendpoint_dummy.cpp
sys/i2c/i2cpacket.cpp
sys/i2c/i2cdispatcher.cpp
master/i3cpacket.cpp
sys/i2c/i2caddress.cpp
sys/i2c/i2cendpoint.cpp
sys/i2c/i2cendpointbroker.cpp
sys/i2c/i2cendpointexception.cpp
master/i3cendpoint.cpp
master/i3cendpointbroker.cpp
master/i3c_commhandler.cpp
master/operation.cpp
${WIRINGPI_FILES}
)
#
# platform/rpi/i2cendpoint_wiringpi.cpp
#
#
#

if (WIRINGPI_LIBRARY)
  # add the target link libraries
  target_link_libraries(i2cmaster ${WIRINGPI_LIBRARY})
  target_link_libraries(i3cmaster ${WIRINGPI_LIBRARY})
endif(WIRINGPI_LIBRARY)

target_link_libraries(i3cmaster ${CONFIG_LIBRARIES})
target_link_libraries(i2cmaster ${CONFIG_LIBRARIES})
