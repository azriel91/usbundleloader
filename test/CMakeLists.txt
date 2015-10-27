add_subdirectory(bundles)

# Create the test binary
if(WIN32)
  string(REPLACE "/" "\\\\" CMAKE_CURRENT_BINARY_DIR_NATIVE ${CMAKE_CURRENT_BINARY_DIR})
  string(REPLACE "/" "\\\\" CMAKE_RUNTIME_OUTPUT_DIRECTORY_NATIVE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else()
  set(CMAKE_CURRENT_BINARY_DIR_NATIVE ${CMAKE_CURRENT_BINARY_DIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_NATIVE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/usBundleLoaderTestConfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/usBundleLoaderTestConfig.h)

set(test_main_TARGET ${PROJECT_NAME}_test_main)
set(static_bundle_deps )
if(NOT BUILD_SHARED_LIBS)
  sl_find_static_lib_paths(static_bundle_deps CppMicroServices)
  set(static_bundle_deps ${static_bundle_deps} TestBundleOne)
endif()
sl_create_bundle(${test_main_TARGET} EXECUTABLE
                 BUNDLE_NAME main
                 SOURCES main.cpp Activator.cpp
                 RESOURCES manifest.json
                 ZIP_ARCHIVES ${static_bundle_deps})
target_link_libraries(${test_main_TARGET} PRIVATE ${PROJECT_NAME} ${CONAN_LIBS} gtest pthread dl TestBundleOne)
sl_disable_gtest_tuple(${test_main_TARGET})

# add custom target so that the test executable is rebuilt when the config header is regenerated
add_custom_target(usBundleLoaderTestConfigTarget DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/usBundleLoaderTestConfig.h)
add_dependencies(${test_main_TARGET} usBundleLoaderTestConfigTarget TestBundleOne)

target_include_directories(${test_main_TARGET} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Run the test
enable_testing()

add_test(NAME ${test_main_TARGET}
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_main_TARGET})
