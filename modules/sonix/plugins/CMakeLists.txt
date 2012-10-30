set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${SNX_LIB_DIR}")

# Target to build all configured backends
add_custom_target(sonix_backends)
set_target_properties(sonix_backends PROPERTIES FOLDER "${VRJUGGLERSUITE_META_PROJECT_FOLDER}")

function(sonix_add_backend _backend_name)
	add_definitions(-D_SNX_PLUGIN_BUILD_)
	add_library(${_backend_name}_snd
		MODULE ${ARGN})

	target_link_libraries(${_backend_name}_drv sonix)

	set_target_properties(${_backend_name}_drv PROPERTIES FOLDER "Sonix backends")
	install(TARGETS ${_backend_name}_drv
		LIBRARY DESTINATION lib/${SNX_LIB_DIR}/plugins COMPONENT sonix-runtime-openal
		RUNTIME DESTINATION lib/${SNX_LIB_DIR}/plugins COMPONENT sonix-runtime-openal)
	add_dependencies(sonix_backends ${_backend_name}_drv)
endfunction()

find_package(ALUT)
if(ALUT_FOUND)
	add_subdirectory(OpenAL)
endif()

#find_package(Audiere)
#if(AUDIERE_FOUND)
#	add_subdirectory(Audiere)
#endif()

#find_package(Subsynth)
#if(SUBSYNTH_FOUND)
#	add_subdirectory(Subsynth)
#endif()
