# A directory to find CppMicroServices sources.
if (EXISTS "${CMAKE_HOME_DIRECTORY}/../deps/azriel/cppmicroservices/CMakeLists.txt")
  set(cppmicroservices_dir "${CMAKE_HOME_DIRECTORY}/../deps/azriel/cppmicroservices")
  include_directories(${cppmicroservices_dir}/cmake)
  include(${cppmicroservices_dir}/cmake/usFunctionCreateTestModule.cmake)
else()
  message(FATAL_ERROR "azriel/cppmicroservices isn't in your project/deps folder")
endif()

add_subdirectory(testModuleOne)
