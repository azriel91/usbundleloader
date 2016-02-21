add_subdirectory(bundles)

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
target_link_libraries(${test_main_TARGET} PRIVATE ${PROJECT_NAME} ${CONAN_LIBS} TestBundleOne)

sl_generate_and_include_custom_header(usBundleLoaderTestConfig.h.in ${test_main_TARGET})
add_dependencies(${test_main_TARGET} TestBundleOne)

sl_include_tests(${test_main_TARGET})
