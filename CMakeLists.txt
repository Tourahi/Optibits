

# - Cannot go higher than CMake 3.22.1 while we support Ubuntu 22.04.
cmake_minimum_required(VERSION 3.22.1...3.26.4 FATAL_ERROR)

project(Optibits VERSION 0.0.0)

##############################################
# Global options

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##############################################
# Declare dependencies

find_package()