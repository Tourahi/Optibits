# Sets the following variables:
#
# LUAJIT_FOUND
# LUAJIT_INCLUDE_DIR
# LUAJIT_LIBRARY

set(LUAJIT_SEARCH_PATHS
    /usr/local
    /usr
    )

find_path(
    NAMES luajit.h
    PATH_SUFFIXES include include/luajit-2.1 include include/luajit-2.0
    PATHS ${LUAJIT_SEARCH_PATHS})

find_library(
    NAMES luajit-5.1
    PATH_SUFFIXES lib
    PATHS ${LUAJIT_SEARCH_PATHS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LuaJIT DEFAULT_MSG LUAJIT_LIBRARY LUAJIT_INCLUDE_DIR)


mark_as_advanced(LUAJIT_INCLUDE_DIR LUAJIT_LIBRARY)

