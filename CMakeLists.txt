project(usBundleLoader)
cmake_minimum_required(VERSION 3.0)

include(conanbuildinfo.cmake)
conan_basic_setup()

# === Dependency discovery === #

# HACK: include cmake functions from other conan projects
# Detect CppMicroServices directory based on a file we expect to exist
find_path(CppMicroServices_CONAN_DIR "CppMicroServicesConfig.cmake" PATHS ${CONAN_INCLUDE_DIRS})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CppMicroServices_CONAN_DIR})
find_package(CppMicroServices 2.99.0 CONFIG)

# Detect sl_cmake directory based on a file we expect to exist
find_path(sl_cmake_DIR "slBundleFunctions.cmake" PATHS ${CONAN_INCLUDE_DIRS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${sl_cmake_DIR})
include(slBundleFunctions)

# === Targets === #
sl_create_bundle(${PROJECT_NAME}
                 SOURCES BundleLoader.cpp
                 RESOURCES manifest.json)
sl_generate_and_include_bundle_header(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

sl_include_test_dir()
