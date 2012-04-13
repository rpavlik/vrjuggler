add_definitions(-D_VRJ_D3D_BUILD_)

set(HEADERS
	App.h
	BasicSimulator.h
	Config.h
	D3dApp.h
	D3dDrawManager.h
	DrawManager.h
	SimInterface.h
	SimInterfaceFactory.h
	SimInterfacePtr.h
	Window.h)

set(SOURCES
	App.cpp
	BasicSimulator.cpp
	DrawManager.cpp
	SimInterface.cpp
	SimInterfaceFactory.cpp
	Window.cpp

	../../../vrj_d3d.rc)

find_package(Direct3D REQUIRED)
include_directories(${DIRECT3D_INCLUDE_DIRS})

add_library(vrj_d3d SHARED ${HEADERS} ${SOURCES})
target_link_libraries(vrj_d3d
	vrj
	${DIRECT3D_LIBRARIES})

set_target_properties(vrj_d3d PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")

vrjugglersuite_set_versioned_library_output_name(vrj_d3d)

install(TARGETS vrj_d3d EXPORT vrjexport
	LIBRARY DESTINATION lib COMPONENT vrj-runtime
	RUNTIME DESTINATION bin COMPONENT vrj-runtime
	ARCHIVE DESTINATION lib COMPONENT vrj-dev)

