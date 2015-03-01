# This CMakeLists.txt file helps defining your block building and compiling
# Include the main biicode macros and functions
# To learn more about the CMake use with biicode, visit http://docs.biicode.com/c++/building.html

project(usBundleLoader)

cmake_minimum_required(VERSION 2.8)

# Initializes block variables
INIT_BIICODE_BLOCK()

set(BII_LIB_SRC BundleLoader.h
                BundleLoader.cpp)

set(BII_test_main_SRC test/main.cpp)

# Actually create targets: executables and libraries.
ADD_BIICODE_TARGETS()

# Only add tests if they exist.
# Typically dependent blocks will not depend on test code and so it would not be downloaded
if(BII_BLOCK_PREFIX MATCHES "^blocks$")
  add_subdirectory(test)
endif()
