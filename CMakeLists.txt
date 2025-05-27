#
# Copyright (c) 2024-2025 Optibits Development Team
#

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
	message(FATAL_ERROR "Prevented in-tree build.")
endif()

cmake_minimum_required(VERSION 3.16)

project(optibits)

set(CMAKE_MODULE_PATH "${optibits_SOURCE_DIR}/extra/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE) # Needed for shared libs on Linux. (-fPIC).
set(CMAKE_CXX_STANDARD 17)

# Extract version.h
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/src/common/version.h OPTIBITS_VERSION_FILE_BLOB)

# Extract one of OPTIBITS_VERSION_MAJ/MIN/REV
function(match_version ARG_STR OUT_VAR)
  string(REGEX MATCH "VERSION_${ARG_STR} = ([0-9]+);" TMP_VER "${OPTIBITS_VERSION_FILE_BLOB}")
  string(REGEX MATCH "[0-9]+" TMP_VER "${TMP_VER}")
  set(${OUT_VAR} ${TMP_VER} PARENT_SCOPE)
endfunction()

match_version("MAJ" OPTIBITS_VERSION_MAJ)
match_version("MIN" OPTIBITS_VERSION_MIN)
match_version("REV" OPTIBITS_VERSION_REV)

