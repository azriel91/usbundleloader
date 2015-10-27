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

#ifndef BUNDLELOADER_H_
#define BUNDLELOADER_H_

#include <usCoreConfig.h>

#if defined(US_PLATFORM_POSIX)
	#include <dlfcn.h>
#elif defined(US_PLATFORM_WINDOWS)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
	#include <strsafe.h>
#else
	#error Unsupported platform
#endif

#include <string>

#include <usBundle.h>
#include <usSharedLibrary.h>

#include "usBundleLoader/Bundle.h"

class USBUNDLELOADER_EXPORT BundleLoader {
private:
	/**
	 * The bundle context of the CppMicroServices framework to use when installing additional bundles.
	 */
	us::BundleContext* const frameworkBundleContext;
	/**
	 * The path to the running executable, from which to load bundles that have been statically linked.
	 */
	const std::string executablePath;

public:
#ifdef US_BUILD_SHARED_LIBS
	/**
	 * Construct a BundleLoader for shared library linking.
	 *
	 * @param frameworkBundleContext the bundle context of the CppMicroServices framework
	 * @param executablePath the path to the running executable
	 */
	BundleLoader(us::BundleContext* frameworkBundleContext);
#else
	/**
	 * Construct a BundleLoader for static library linking.
	 *
	 * @param frameworkBundleContext the bundle context of the CppMicroServices framework
	 * @param executablePath the path to the running executable
	 */
	BundleLoader(us::BundleContext* frameworkBundleContext, const std::string executablePath);
#endif
	virtual ~BundleLoader();

	/**
	 * Load the bundle that has been statically compiled into the running executable.
	 *
	 * @param bundleName the name of the bundle to load
	 */
	us::Bundle* Load(const std::string bundleName);
	/**
	 * Load the bundle for the given shared library.
	 *
	 * @param bundleName the name of the bundle to load
	 * @param libraryPath the path to the bundle library
	 */
	us::Bundle* Load(const std::string bundleName, const std::string libraryPath);
	/**
	 * Unloads the given bundle.
	 *
	 * @param bundle the bundle to unload
	 */
	void Unload(us::Bundle* bundle);
};

#endif /* BUNDLELOADER_H_ */
