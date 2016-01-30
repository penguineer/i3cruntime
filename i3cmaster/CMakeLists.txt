cmake_minimum_required(VERSION 2.8.9)

project (I3CMASTER CXX)

set(CMAKE_CXX_FLAGS "-std=c++14")

### Check and select the I2C library
# dummy is the default
set(I2C_ENDPOINT_IMPL "dummy")
# do we have wiringPi?
#find_library(WIRINGPI_LIBRARY NAMES wiringPi wiringPiDev)
#if (WIRINGPI_LIBRARY)
#  # use this implementation instead and add the target
#  # link libraries
#  set(I2C_ENDPOINT_IMPL "wiringpi")
#endif(WIRINGPI_LIBRARY)

# if wiringPi has been includedr
if (I2C_ENDPOINT_IMPL STREQUAL "wiringpi")
  # add link targets for the wiringPi libraries
  # WIRINGPI_LIBRARY has already been checked before
  target_link_libraries(i3cmaster ${WIRINGPI_LIBRARY})
endif (I2C_ENDPOINT_IMPL STREQUAL "wiringpi")



#add_executable(i3cmaster i3c_commhandler.cpp packet.cpp master.cpp
#	i2cendpoint.cpp i3cendpoint.cpp  i3cendpoint_dummy.cpp i2cendpoint_dummy.cpp)
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
)

add_executable(i2cmaster
debug.cpp
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
#master/i3c_commhandler.cpp
master/operation.cpp
)
#
# platform/rpi/i2cendpoint_wiringpi.cpp
#
#
#
