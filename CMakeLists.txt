cmake_minimum_required(VERSION 3.16)

project(optibits)

# Enforce out-of-source build
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build.")
endif()

# Basic CMake settings
set(CMAKE_MODULE_PATH "${optibits_SOURCE_DIR}/extra/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Extract version from version.h
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/src/common/version.h OPTIBITS_VERSION_FILE_BLOB)

function(match_version ARG_STR OUT_VAR)
    string(REGEX MATCH "VERSION_${ARG_STR} = ([0-9]+);" TMP_VER "${OPTIBITS_VERSION_FILE_BLOB}")
    string(REGEX MATCH "[0-9]+" TMP_VER "${TMP_VER}")
    set(${OUT_VAR} ${TMP_VER} PARENT_SCOPE)
endfunction()

match_version("MAJ" OPTIBITS_VERSION_MAJ)
match_version("MIN" OPTIBITS_VERSION_MIN)
match_version("REV" OPTIBITS_VERSION_REV)

set(OPTIBITS_VERSION_STR "${OPTIBITS_VERSION_MAJ}.${OPTIBITS_VERSION_MIN}")
message(STATUS "Version: ${OPTIBITS_VERSION_STR}")

# Platform-related naming
set(OPTIBITS_EXE_NAME optibits CACHE STRING "The name of the executable")
set(OPTIBITS_DEFAULT_LIB_NAME liboptibits)
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(OPTIBITS_DEFAULT_LIB_NAME "${OPTIBITS_EXE_NAME}-${OPTIBITS_VERSION_STR}")
    message(STATUS "Linux enjoyer -> ${OPTIBITS_DEFAULT_LIB_NAME}")
endif()
set(OPTIBITS_LIB_NAME ${OPTIBITS_DEFAULT_LIB_NAME} CACHE STRING "")
set(OPTIBITS_CONSOLE_EXE_NAME "${OPTIBITS_EXE_NAME}c" CACHE STRING "")

# Architecture check
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OPTIBITS_X64 TRUE)
    set(OPTIBITS_TARGET_PLATFORM x64)
else()
    set(OPTIBITS_X86 TRUE)
    set(OPTIBITS_TARGET_PLATFORM x86)
endif()


message(STATUS "Target platform: ${LOVE_TARGET_PLATFORM}")

# SDL (Simple DirectMedia Layer) providing low-level access to audio, keyboard, mouse, joystick, and graphics hardware
add_library(optidep::SDL INTERFACE IMPORTED)

# Freetype for font rendering
add_library(optidep::Freetype INTERFACE IMPORTED)

# Harfbuzz for text shaping, converting Unicode text to glyph indices and positions for proper rendering
add_library(optidep::Harfbuzz INTERFACE IMPORTED)

# (Open Audio Library) is a cross-platform 3D audio API
add_library(optidep::OpenAL INTERFACE IMPORTED)

# (libmodplug) for decoding mod-like music formats
add_library(optidep::Modplug INTERFACE IMPORTED)

# optidep video compression format from the Xiph.Org Foundation
add_library(optidep::Theora INTERFACE IMPORTED)

# Vorbis audio coding format and a software reference encoder/decoder (codec)
add_library(optidep::Vorbis INTERFACE IMPORTED)

# Ogg multimedia container format
add_library(optidep::Ogg INTERFACE IMPORTED)

# Zlib lossless data compression library
add_library(optidep::Zlib INTERFACE IMPORTED)

# we know this dude
add_library(optidep::Lua INTERFACE IMPORTED)

# required for enet
add_definitions(-D HAS_SOCKLEN_T)

# LINUX centric build for now

find_package(SDL3 3.1.3 REQUIRED CONFIG)
target_include_directories(optidep::SDL INTERFACE ${SDL3_INCLUDE_DIRS})
target_link_libraries(optidep::SDL INTERFACE ${SDL3_LIBRARIES})

find_package(Freetype REQUIRED)
target_include_directories(optidep::Freetype INTERFACE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(optidep::Freetype INTERFACE ${FREETYPE_LIBRARY})


find_package(Harfbuzz REQUIRED)
target_include_directories(optidep::Harfbuzz INTERFACE ${HARFBUZZ_INCLUDE_DIR})
target_link_libraries(optidep::Harfbuzz INTERFACE ${HARFBUZZ_LIBRARY})

find_package(OpenAL REQUIRED)
target_include_directories(optidep::OpenAL INTERFACE ${OPENAL_INCLUDE_DIR})
target_link_libraries(optidep::OpenAL INTERFACE ${OPENAL_LIBRARY})

find_package(ModPlug REQUIRED)
target_include_directories(optidep::Modplug INTERFACE ${MODPLUG_INCLUDE_DIR})
target_link_libraries(optidep::Modplug INTERFACE ${MODPLUG_LIBRARY})

find_package(Theora REQUIRED)
target_include_directories(optidep::Theora INTERFACE ${THEORA_INCLUDE_DIR})
target_link_libraries(optidep::Theora INTERFACE ${THEORA_LIBRARY} ${THEORADEC_LIBRARY})

find_package(Vorbis REQUIRED)
target_include_directories(optidep::Vorbis INTERFACE ${VORBIS_INCLUDE_DIR})
target_link_libraries(optidep::Vorbis INTERFACE ${VORBISFILE_LIBRARY})

find_package(Ogg REQUIRED)
target_include_directories(optidep::Ogg INTERFACE ${OGG_INCLUDE_DIR})
target_link_libraries(optidep::Ogg INTERFACE ${OGG_LIBRARY})

find_package(ZLIB REQUIRED)
target_include_directories(optidep::Zlib INTERFACE ${ZLIB_INCLUDE_DIRS})
target_link_libraries(optidep::Zlib INTERFACE ${ZLIB_LIBRARY})



set(DISABLE_WARNING_FLAG -w)

#
# common
#
add_library(optibits_common STATIC
  src/common/config.h
  src/common/int.h
  src/common/Optional.h
  src/common/types.cpp
  src/common/types.h
  src/common/Knot.h
  src/common/Knot.cpp
  src/common/memory.h
  src/common/memory.cpp
)
target_link_libraries(optibits_common PUBLIC
  optidep::Lua
  optidep::SDL
)


#
# liboptibits
#
include_directories(
  BEFORE
  src
  src/libs
  src/modules
  src/spec
)


add_library(liboptibits SHARED
  src/modules/optibits/optibits.cpp
)
set_target_properties(liboptibits PROPERTIES
  C_VISIBILITY_PRESET hidden
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
  LIBRARY_OUTPUT_NAME "${OPTIBITS_LIB_NAME}")
set(LIBOPTIBITS_DEPENDENCIES
  optibits_common
)
target_link_libraries(liboptibits ${LIBOPTIBITS_DEPENDENCIES})


#
# optibits (executable)
#
add_executable(optibits WIN32)

target_sources(optibits PRIVATE src/optibits.cpp)
target_link_libraries(optibits liboptibits)
set_target_properties(optibits PROPERTIES
  C_VISIBILITY_PRESET hidden
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
  OUTPUT_NAME ${OPTIBITS_EXE_NAME})


#
# tests
#

# (executable)
add_executable(tests
  src/spec/test_optional.cpp
  src/spec/test_main.cpp
)
enable_testing()
add_test(NAME Tests COMMAND tests)
