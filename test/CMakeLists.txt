add_subdirectory(modules)

# Create the test binary
if(WIN32)
  string(REPLACE "/" "\\\\" CMAKE_CURRENT_BINARY_DIR_NATIVE ${CMAKE_CURRENT_BINARY_DIR})
else()
  set(CMAKE_CURRENT_BINARY_DIR_NATIVE ${CMAKE_CURRENT_BINARY_DIR})
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/usBundleLoaderTestConfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/usBundleLoaderTestConfig.h)

# add custom target so that the test executable is rebuilt when the config header is regenerated
add_custom_target(usBundleLoaderTestConfigTarget DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/usBundleLoaderTestConfig.h)
add_dependencies(${BII_test_main_TARGET} usBundleLoaderTestConfigTarget TestModuleOne)

target_include_directories(${BII_test_main_TARGET} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Run the test
enable_testing()

add_test(NAME ${BII_test_main_TARGET}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${BII_test_main_TARGET})
