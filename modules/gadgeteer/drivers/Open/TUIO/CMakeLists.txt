if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	add_definitions(-DMACOSX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "HP") # FIXME is this the proper system name?
	add_definitions(-DHP)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_definitions(-DLINUX -DUNIX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Solaris") # FIXME is this the proper system name?
	add_definitions(-DSUN)
elseif(WIN32)
	# No extra definitions needed
else()
	message("CMAKE_SYSTEM_NAME is [${CMAKE_SYSTEM_NAME}]. We're not handling this case yet!")
endif()

set(OSCPACK_SOURCES 
#	oscpack/osc/MessageMappingOscPacketListener.h
#	oscpack/osc/OscException.h
#	oscpack/osc/OscHostEndianness.h
#	oscpack/osc/OscOutboundPacketStream.cpp
#	oscpack/osc/OscOutboundPacketStream.h
#	oscpack/osc/OscPacketListener.h
#	oscpack/osc/OscPrintReceivedElements.cpp
#	oscpack/osc/OscPrintReceivedElements.h
	oscpack/osc/OscReceivedElements.cpp
	oscpack/osc/OscReceivedElements.h
#	oscpack/osc/OscTypes.cpp
#	oscpack/osc/OscTypes.h
)
source_group(oscpack FILES ${OSCPACK_SOURCES})
gadgeteer_add_driver(TUIO 
	Tuio.cpp
	Tuio.h
	Tuio.rc
	TuioPoint.h
	TuioStandalone.cpp
	TuioStandalone.h
	${OSCPACK_SOURCES})

if(WIN32)
	target_link_libraries(TUIO_drv ws2_32)
endif()