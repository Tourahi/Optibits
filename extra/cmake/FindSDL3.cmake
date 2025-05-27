# Sets the following variables:
#
#  SDL3_FOUND
#  SDL3_INCLUDE_DIR
#  SDL3_LIBRARY

set(SDL3_SEARCH_PATHS
	/usr/local
	/usr
	)

find_path(SDL3_INCLUDE_DIR
	NAMES SDL.h
	PATH_SUFFIXES include include/SDL3
	PATHS ${SDL3_SEARCH_PATHS})

find_library(SDL3_LIBRARY
	NAMES SDL3
	PATH_SUFFIXES lib
	PATHS ${SDL3_SEARCH_PATHS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL3 DEFAULT_MSG SDL3_LIBRARY SDL3_INCLUDE_DIR)

mark_as_advanced(SDL3_INCLUDE_DIR SDL3_LIBRARY)
