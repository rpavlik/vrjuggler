# - try to find Java's IDLJ Interface Definition Language compiler.
#
# Ideally used with CMake 2.8.5 or newer for Java support using FindJava.cmake
# and UseJava.cmake
#
# Variables:
#  Java_IDLJ_COMMAND, executable for idlj
#  IDLJ_FOUND, If false, do not try to use this
#
# Function:
#  java_idlj(varname idlfile [extra idlj args]) - Adds a custom command to generate
#    the Java source files from the IDL file you indicate, and
#    appends filenames suitable to add to a add_jar() call to the
#    variable you specified.
#
# Because the files generated from an IDL file are not entirely predictable,
# java_idlj will add a stamp file (for dependency handling) and an ant-style
# wildcard to your list of filenames; this approach works fine with CMake 2.8.5+
# Java support. Files are generated in a directory created specifically for
# the particular IDL file and the particular call, in the build directory -
# there should be no worries about overwriting files or picking up too much
# with the wildcard.
#
# You may wish to add the IDL file to your list of sources if you want it
# to appear in your IDE, but it is not necessary.
#
# Original Author:
# 2012 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com
# Iowa State University HCI Graduate Program/VRAC
#
# Copyright Iowa State University 2012.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

if(NOT JAVA_FOUND)
	find_package(Java QUIET)
endif()

if(JAVA_FOUND)
	get_filename_component(JAVA_BIN_DIR "${Java_JAVAC_EXECUTABLE}" PATH)
	find_program(Java_IDLJ_COMMAND
		idlj
		HINTS
		${JAVA_BIN_DIR}
	)
endif()

# handle the QUIETLY and REQUIRED arguments and set xxx_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IDLJ
	DEFAULT_MSG
	Java_IDLJ_COMMAND
	JAVA_FOUND)

if(IDLJ_FOUND)
	function(java_idlj _varname _idlfile)
		get_filename_component(_idl_name "${_idlfile}" NAME_WE)
		
		message(STATUS "Adding IDLJ processing command for ${_idl_name} aka ${_idlfile}")
		set(outdir "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/idlj/${_idl_name}.dir")
		set(stampfile "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/idlj/${_idl_name}.stamp")
		list(APPEND ${_varname} 
			"${stampfile}"
			"${outdir}/*")
		add_custom_command(OUTPUT
			"${stampfile}"
			COMMAND
			"${Java_IDLJ_COMMAND}" -verbose -fclient -fallTIE -td "${outdir}" ${ARGN} "${_idlfile}"
			COMMAND
			"${CMAKE_COMMAND}" -E touch "${stampfile}"
			DEPENDS
			"${_idlfile}"
			WORKING_DIRECTORY
			"${CMAKE_CURRENT_SOURCE_DIR}"
			COMMENT
			"Processing ${_idlfile} with Java's idlj")
		
		set(${_varname} ${${_varname}} PARENT_SCOPE)
		set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${outdir}" "${stampfile}")
	endfunction()
endif()

mark_as_advanced(Java_IDLJ_COMMAND)
