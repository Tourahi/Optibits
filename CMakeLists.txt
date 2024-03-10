

# - Cannot go higher than CMake 3.22.1 while we support Ubuntu 22.04.
cmake_minimum_required(VERSION 3.22.1...3.26.4 FATAL_ERROR)

project(Optibits VERSION 0.0.0)

##############################################
# Global options

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##############################################
# Declare dependencies

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FONTCONFIG REQUIRED fontconfig)

##############################################
# Create target and set properties


file(GLOB_RECURSE C_DEPS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/deps/*.c)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/Optibits/*.hpp)
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(optibits ${C_DEPS_FILES} ${HEADER_FILES} ${SOURCE_FILES})


target_compile_features(optibits PUBLIC cxx_std_20)

set_property(TARGET optibits PROPERTY POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(optibits PRIVATE -DOPTIBITS_DEPRECATED=)

target_include_directories(optibits PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_include_directories(optibits SYSTEM PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/mojoAL/AL
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL_sound
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/utf8proc)


target_link_libraries(optibits PRIVATE
  SDL2::SDL2
  OpenGL::GL
  # Linux
  ${FONTCONFIG_LIBRARIES})


##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Optibits)

install(TARGETS optibits
  EXPORT optibits-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})



set_target_properties(optibits PROPERTIES EXPORT_NAME Optibits)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(EXPORT optibits-targets
  FILE OptibitsTargets.cmake
  NAMESPACE Optibits::
  DESTINATION ${INSTALL_CONFIGDIR})


include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/Config.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR})


install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/Config.cmake
  DESTINATION ${INSTALL_CONFIGDIR})

export(EXPORT optibits-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/OptibitsTargets.cmake
  NAMESPACE Optibits::)


add_library(Optibits::Optibits ALIAS optibits)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  enable_testing()
  add_subdirectory(test)
endif ()