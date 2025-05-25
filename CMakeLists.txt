cmake_minimum_required(VERSION 3.25)

project(optibits)

cmake_policy(SET CMP0054 NEW)

cmake_policy(SET CMP0063 NEW)

# Directory for easier includes
# Anywhere you see include(...) you can check <root>/cmake for that file
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Sets compiler flags and language standard
include(CompilerFlags)
