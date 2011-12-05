
if(__juggler_suite_default_options)
	return()
endif()
set(__juggler_suite_default_options YES)

get_filename_component(VRJUGGLERSUITE_MODULE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
list(APPEND CMAKE_MODULE_PATH "${VRJUGGLERSUITE_MODULE_DIR}")

if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()
if(NOT SHARE_OUTPUT_DIRECTORY)
	set(SHARE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/share)
endif()

if(WIN32)
	set(DEFAULT_VERSIONED OFF)
else()
	set(DEFAULT_VERSIONED ON)
endif()
option(BUILD_VERSIONED_DIRECTORIES "Should we version the directories for plugins and data?" ${DEFAULT_VERSIONED})

if(MSVC)
	option(BUILD_WITHOUT_COMMON_WARNINGS "Should we disable some distracting build warnings?" ON)
	# Disable some warnings
	# 4275: non dll-interface class used as base for dll-interface class
	# 4251: needs to have dll-interface to be used by clients of class
	if(BUILD_WITHOUT_COMMON_WARNINGS)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4275 /wd4251")
	endif()
endif()

if(WIN32)
	add_definitions(-DCPPDOM_DYN_LINK -DBOOST_ALL_DYN_LINK)
endif()

function(vrjugglersuite_create_version_rc)
	configure_file("${VRJUGGLERSUITE_MODULE_DIR}/version.rc.cmake_in" "${CMAKE_CURRENT_BINARY_DIR}/version.rc")
endfunction()
