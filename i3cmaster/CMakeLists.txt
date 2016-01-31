cmake_minimum_required(VERSION 2.8.9)

project (I3CMASTER CXX)

set(CMAKE_CXX_FLAGS "-std=c++14")

### Check the I2C library

# do we have wiringPi?
find_library(WIRINGPI_LIBRARY NAMES wiringPi wiringPiDev)
find_library(LIBCONFIG_LIBRARIES NAMES libconfig libconfig++)

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
master/i3cendpointbroker.cpp
#master/i3c_commhandler.cpp
master/operation.cpp
# ${WIRINGPI_FILES}
)


if (WIRINGPI_LIBRARY)
  # add the target link libraries
  target_link_libraries(i3cmaster ${WIRINGPI_LIBRARY})
  set(WIRINGPI_FILES
      platform/rpi/wiringpii2cendpoint.cpp
      platform/rpi/wiringpii2cendpointbroker.cpp
  )
endif(WIRINGPI_LIBRARY)

if (LIBCONFIG_LIBRARIES)
	target_link_libraries(i2cmaster ${LIBCONFIG_LIBRARIES})
endif(LIBCONFIG_LIBRARIES)

add_executable(i2cmaster
# debug.cpp
master/i2cmaster.cpp
platform/dummy/i2cendpoint_dummy.cpp
sys/i2c/i2cpacket.cpp
sys/i2c/i2cdispatcher.cpp
master/i3cpacket.cpp
sys/i2c/i2caddress.cpp
sys/i2c/i2cendpoint.cpp
sys/i2c/i2cendpointexception.cpp
master/i3cendpoint.cpp
master/i3cendpointbroker.cpp
master/i3c_commhandler.cpp
master/operation.cpp
# ${WIRINGPI_FILES}
)
#
# platform/rpi/i2cendpoint_wiringpi.cpp
#
#
#
