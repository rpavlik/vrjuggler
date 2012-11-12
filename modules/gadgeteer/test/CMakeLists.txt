# These tests are effectively "header-only", so we just need to link against
# VPR. (If these don't build, neither will the library...)
foreach(APP TypeHelpers-Pow TypeHelpers-OrderedBases TypeHelpers-Id)
	add_executable(gadgeteer_${APP} ${APP}.cpp)
	target_link_libraries(gadgeteer_${APP} vpr)
	set_target_properties(gadgeteer_${APP} PROPERTIES FOLDER "Gadgeteer tests")
	add_test(NAME Gadgeteer-${APP}
		COMMAND gadgeteer_${APP})
endforeach()

