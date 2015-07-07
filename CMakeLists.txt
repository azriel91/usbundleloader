project(${BII_BLOCK_NAME})

set(BII_LIB_SRC BundleLoader.cpp)
set(BII_test_main_SRC test/main.cpp)
usFunctionGenerateModuleInit(BII_test_main_SRC MODULE_NAME main)

# Actually create targets: executables and libraries.
ADD_BII_TARGETS()

# Build tests only if this block is not retrieved as a dependency
if(NOT ${BII_IS_DEP})
  add_subdirectory(test)

  set_property(TARGET ${BII_test_main_TARGET} APPEND PROPERTY COMPILE_DEFINITIONS US_MODULE_NAME=main)

  if (NOT ${BUILD_SHARED_LIBS})
    target_link_libraries(${BII_test_main_TARGET} PRIVATE TestModuleOne)
    target_compile_definitions(${BII_test_main_TARGET} PRIVATE US_STATIC_MODULE)
  endif()
endif()
