project(usBundleLoader)

cmake_minimum_required(VERSION 2.8)

set(BII_LIB_SRC BundleLoader.cpp)
set(BII_test_main_SRC test/main.cpp)

# Actually create targets: executables and libraries.
ADD_BIICODE_TARGETS()

# Build tests only if this block is not retrieved as a dependency
if(NOT ${BII_IS_DEP})
  add_subdirectory(test)
endif()
