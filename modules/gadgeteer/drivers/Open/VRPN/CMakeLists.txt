include_directories(${VRPN_INCLUDE_DIRS})

find_package(Libusb1)
include_directories(${LIBUSB1_INCLUDE_DIRS})
list(APPEND VRPN_LIBRARIES ${LIBUSB1_LIBRARIES})

gadgeteer_add_driver(VRPN vrpn.rc Vrpn.cpp Vrpn.h)
target_link_libraries(VRPN_drv ${VRPN_LIBRARIES})
