# This CMakeLists.txt file helps defining your block building and compiling
# Include the main biicode macros and functions
# To learn more about the CMake use with biicode, visit http://docs.biicode.com/c++/building.html

project(usBundleLoader)

cmake_minimum_required(VERSION 2.8)

include(${CMAKE_HOME_DIRECTORY}/biicode.cmake)

# Initializes block variables
INIT_BIICODE_BLOCK()

# Actually create targets: EXEcutables and libraries.
ADD_BIICODE_TARGETS()
