project(${BII_BLOCK_NAME})

set(BII_LIB_SRC BundleLoader.cpp)
set(BII_test_main_SRC test/main.cpp)

# Actually create targets: executables and libraries.
ADD_BII_TARGETS()

# Build tests only if this block is not retrieved as a dependency
if(NOT ${BII_IS_DEP})
  add_subdirectory(test)
endif()
