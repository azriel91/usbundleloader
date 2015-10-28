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
#include "../BundleLoader.h"

#ifndef US_BUILD_SHARED_LIBS
	#include <usBundleImport.h>
	US_IMPORT_BUNDLE(CppMicroServices)
	US_IMPORT_BUNDLE(TestBundleOne)
	US_IMPORT_BUNDLE(main)
#endif

BundleLoader* bundleLoader = nullptr;

TEST(UsBundleLoader, LoadsBundles) {
	try {
		bundleLoader->Load("TestBundleOne");

		us::BundleContext* const bundleContext = us::GetBundleContext();
		EXPECT_TRUE(bundleContext->GetBundle("TestBundleOne") != nullptr);
	} catch (const std::exception& e) {
		FAIL() << e.what();
	}
}

TEST(UsBundleLoader, UnloadsBundles) {
	try {
#ifdef US_BUILD_SHARED_LIBS
		printf("Loading: '%s'\n", BUNDLE_ONE_LIB_PATH.c_str());
		us::Bundle* const bundle = bundleLoader->Load("TestBundleOne", BUNDLE_ONE_LIB_PATH);
#else
		us::Bundle* const bundle = bundleLoader->Load("TestBundleOne");
#endif
		bundleLoader->Unload(bundle);

		us::BundleContext* const bundleContext = us::GetBundleContext();
		EXPECT_TRUE(bundleContext->GetBundle("TestBundleOne") == nullptr);
	} catch (const std::exception& e) {
		FAIL() << e.what();
	}
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	us::FrameworkFactory factory;
	us::Framework* const framework = factory.NewFramework(std::map<std::string, std::string>());
	framework->Start();

#ifdef US_BUILD_SHARED_LIBS
	bundleLoader = new BundleLoader(framework->GetBundleContext(), TEST_BUNDLE_ONE_DIR);
	bundleLoader->Load(std::string("main"), std::string(argv[0]));
#else
	bundleLoader = new BundleLoader(framework->GetBundleContext(), std::string(argv[0]));
	bundleLoader->Load(std::string("main"));
#endif

	return RUN_ALL_TESTS();
}
