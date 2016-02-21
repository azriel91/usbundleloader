sl_create_bundle(TestBundleOne
                 SOURCES TestBundleOneActivator.cpp
                 RESOURCES manifest.json)
target_link_libraries(TestBundleOne CppMicroServices)