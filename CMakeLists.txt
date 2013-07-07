cmake_minimum_required(VERSION 2.6.2)
project(VRJuggler)

###
# Configuration
###
include(CTest)
include(scripts/cmake/VRJugglerSuiteDefaultOptions.cmake)

###
# Recurse into subdirectories
###
add_subdirectory(modules)

###
# Version
###
set(CPACK_PACKAGE_VENDOR "Iowa State University")
set(CPACK_PACKAGE_CONTACT "Ryan Pavlik <rpavlik@iastate.edu>")
get_property(CPACK_PACKAGE_VERSION_MAJOR GLOBAL PROPERTY VRJ_MAJOR_VER)
get_property(CPACK_PACKAGE_VERSION_MINOR GLOBAL PROPERTY VRJ_MINOR_VER)
get_property(CPACK_PACKAGE_VERSION_PATCH GLOBAL PROPERTY VRJ_PATCH_VER)
set(CPACK_PACKAGE_VERSION
  "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

message(STATUS "")
message(STATUS "VR Juggler Suite version ${CPACK_PACKAGE_VERSION} successfully configured!")

# ---------------------------------------------------------------- Environment
get_property(VRJUGGLER_VERSION_MAJOR GLOBAL PROPERTY VRJ_MAJOR_VER)
get_property(VRJUGGLER_VERSION_MINOR GLOBAL PROPERTY VRJ_MINOR_VER)
get_property(VRJUGGLER_VERSION_PATCH GLOBAL PROPERTY VRJ_PATCH_VER)

export(TARGETS vpr vrj vrj_ogl gadget sonix jccl # tweek
  FILE "${PROJECT_BINARY_DIR}/VRJugglerLibraryDepends.cmake")

export(PACKAGE VRJuggler)

# ------------------------------------------------------- VRJugglerConfig.cmake
# This makes it easier for other cmake based projects to find and use
# VRJuggler. The VRJugglerConfig.cmake will have all the required cmake
# variables needed.

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/VRJugglerConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/VRJugglerConfig.cmake
  @ONLY)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/VRJugglerConfigVersion.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/VRJugglerConfigVersion.cmake
  @ONLY)
