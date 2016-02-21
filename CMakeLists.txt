project(usBundleLoader)
cmake_minimum_required(VERSION 3.0)

include(conanbuildinfo.cmake)
conan_basic_setup()

find_package(CppMicroServices 3.0.0 CONFIG PATHS ${CONAN_CPPMICROSERVICES_ROOT})
include(slBundleFunctions)

# === Targets === #
sl_create_bundle(${PROJECT_NAME}
                 SOURCES src/BundleLoader.cpp
                 RESOURCES manifest.json)
sl_generate_and_include_bundle_header(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

sl_include_test_dir()
