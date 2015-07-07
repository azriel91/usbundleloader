# We have to set US_BUILD_SHARED_LIBS to ${BUILD_SHARED_LIBS} because usFunctionCreateTestModule compiles test modules
# as static modules if either is OFF or undefined
set(US_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

usFunctionCreateTestModule(TestModuleOne TestModuleOneActivator.cpp)

target_link_libraries(TestModuleOne ${BII_LIB_DEPS})
