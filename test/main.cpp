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

#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include <usBundle.h>
#include <usBundleContext.h>
#include <usFramework.h>
#include <usFrameworkFactory.h>
#include <usGetBundleContext.h>

#include "usBundleLoaderTestConfig.h"

#ifdef US_BUILD_SHARED_LIBS
	#include "../BundleLoader.h"
#else
	#include <usBundleImport.h>
	US_IMPORT_BUNDLE(CppMicroServices)
	US_IMPORT_BUNDLE(TestBundleOne)
	US_IMPORT_BUNDLE(main)
#endif

TEST(UsBundleLoader, LoadsBundles) {
	try {
		us::BundleContext* bundleContext = us::GetBundleContext();
#ifdef US_BUILD_SHARED_LIBS
		BundleLoader bundleLoader;

		printf("Loading: '%s'\n", BUNDLE_ONE_LIB_PATH.c_str());
		// bundleLoader.load(BUNDLE_ONE_LIB_PATH);
		bundleContext->InstallBundle(BUNDLE_ONE_LIB_PATH + "/TestBundleOne");
#endif
		std::vector<us::Bundle*> bundles = bundleContext->GetBundles();
		for (us::Bundle* bundle : bundles) {
			std::string name = bundle->GetName();
			printf("%s\n", name.c_str());
		}

		EXPECT_TRUE(bundleContext->GetBundle("TestBundleOne") != NULL);
	} catch (const std::exception& e) {
		FAIL() << e.what();
	}
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	us::FrameworkFactory factory;
	us::Framework* framework = factory.NewFramework(std::map<std::string, std::string>());
	framework->Start();

	us::BundleContext* frameworkBundleContext = framework->GetBundleContext();
	us::Bundle* mainBundle = frameworkBundleContext->InstallBundle(std::string(argv[0]) + "/main");
	mainBundle->Start();

	us::Bundle* testBundleOne = frameworkBundleContext->InstallBundle(std::string(argv[0]) + "/TestBundleOne");
	testBundleOne->Start();

	return RUN_ALL_TESTS();
}
