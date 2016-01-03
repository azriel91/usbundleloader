/*=============================================================================

	Bundle Loader for CppMicroServices

	Copyright (c) Azriel Hoh

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

#include <memory>
#include <usBundle.h>
#include <usBundleContext.h>

#include "BundleLoader.h"

#ifdef US_PLATFORM_WINDOWS
	const std::string BundleLoader::DIR_SEP = "\\";
	const std::string BundleLoader::EXE_EXT = ".exe";
	const std::string BundleLoader::LIB_PREFIX = "";
	const std::string BundleLoader::LIB_EXT = ".dll";
#else
	const std::string BundleLoader::DIR_SEP = "/";
	const std::string BundleLoader::EXE_EXT = "";
	const std::string BundleLoader::LIB_PREFIX = "lib";
	#if defined US_PLATFORM_APPLE
		const std::string BundleLoader::LIB_EXT = ".dylib";
	#else
		const std::string BundleLoader::LIB_EXT = ".so";
	#endif
#endif

BundleLoader::BundleLoader(us::BundleContext* frameworkBundleContext, const std::string libraryPath) :
		frameworkBundleContext(frameworkBundleContext),
		libraryPath(libraryPath) {
}

BundleLoader::~BundleLoader() {
}

std::shared_ptr<us::Bundle> BundleLoader::Load(const std::string bundleName) {
#ifdef US_BUILD_SHARED_LIBS
	return Load(bundleName, this->libraryPath + BundleLoader::DIR_SEP + BundleLoader::LIB_PREFIX + bundleName +
			BundleLoader::LIB_EXT);
#else
	return Load(bundleName, this->libraryPath);
#endif
}

std::shared_ptr<us::Bundle> BundleLoader::Load(const std::string bundleName, const std::string bundleFilePath) {
	std::shared_ptr<us::Bundle> bundle = frameworkBundleContext->InstallBundle(bundleFilePath + "/" + bundleName);
	bundle->Start();
	return bundle;
}

void BundleLoader::Unload(std::shared_ptr<us::Bundle> bundle) {
	bundle->Stop();
	bundle->Uninstall();
}
