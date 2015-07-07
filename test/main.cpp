/*=============================================================================

	Library: CppMicroServices

	Copyright (c) German Cancer Research Center,
		Division of Medical and Biological Informatics

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

=============================================================================*/

#include <azriel/cppmicroservices/core/include/usModule.h>
#include <azriel/cppmicroservices/core/include/usModuleRegistry.h>
#include <google/gtest/gtest.h>
#include <cstdio>
#include <string>

#include "usBundleLoaderTestConfig.h"

#ifdef US_BUILD_SHARED_LIBS
	#include "../BundleLoader.h"
#else
	#include <azriel/cppmicroservices/core/include/usModuleImport.h>
	US_IMPORT_MODULE(CppMicroServices)
	US_IMPORT_MODULE(TestModuleOne)
	US_INITIALIZE_STATIC_MODULE(main)
#endif

US_USE_NAMESPACE

TEST(usBundleLoader, LoadsBundles) {
	try {
#ifdef US_BUILD_SHARED_LIBS
		BundleLoader bundleLoader;

		printf("Loading: '%s'\n", MODULE_ONE_LIB_PATH.c_str());
		bundleLoader.load(MODULE_ONE_LIB_PATH);
#endif

		EXPECT_TRUE(ModuleRegistry::GetModule("TestModuleOne") != NULL);
	} catch (const std::exception& e) {
		FAIL() << e.what();
	}
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
