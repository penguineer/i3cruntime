cmake_minimum_required(VERSION 2.8.9)

project (I3CMASTER)
add_executable(i3cmaster i3c_commhandler.cpp packet.cpp master.cpp
	i2cendpoint.cpp i3cendpoint.cpp i2cendpoint_dummy.cpp)

set(CMAKE_C_FLAGS "-std=c++14")

### Check and select the I2C library
# dummy is the default
set(I2C_ENDPOINT_IMPL "dummy")
# do we have wiringPi?
find_library(WIRINGPI_LIBRARY NAMES wiringPi wiringPiDev)
#if (WIRINGPI_LIBRARY)
#  # use this implementation instead and add the target
#  # link libraries
#  set(I2C_ENDPOINT_IMPL "wiringpi")
#endif(WIRINGPI_LIBRARY)

# if wiringPi has been included
if (I2C_ENDPOINT_IMPL STREQUAL "wiringpi")
  # add link targets for the wiringPi libraries
  # WIRINGPI_LIBRARY has already been checked before
  target_link_libraries(i3cmaster ${WIRINGPI_LIBRARY})
endif (I2C_ENDPOINT_IMPL STREQUAL "wiringpi")




