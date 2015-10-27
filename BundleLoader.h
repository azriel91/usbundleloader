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
	static const std::string DIR_SEP;
	static const std::string EXE_EXT;
	static const std::string LIB_EXT;
	static const std::string LIB_PREFIX;

	/**
	 * The bundle context of the CppMicroServices framework to use when installing additional bundles.
	 */
	us::BundleContext* const frameworkBundleContext;
	/**
	 * If building statically, the path to the running executable from which to load bundles that have been statically
	 * linked.
	 *
	 * If building dynamically, the path to the library directory from which to load bundles from.
	 */
	const std::string libraryPath;

public:
	/**
	 * Construct a BundleLoader.
	 *
	 * @param frameworkBundleContext the bundle context of the CppMicroServices framework
	 * @param libraryPath the path to the running executable if building statically, or to the shared library directory
	 *                    if building shared library bundles.
	 */
	BundleLoader(us::BundleContext* frameworkBundleContext, const std::string libraryPath);
	virtual ~BundleLoader();

	/**
	 * Load the bundle of the given name.
	 *
	 * If building static bundles, this loads the bundle that has been statically compiled into the running executable.
	 * If building shared bundles, this loads the bundle from the libraryDirectory.
	 *
	 * @param bundleName the name of the bundle to load
	 */
	us::Bundle* Load(const std::string bundleName);
	/**
	 * Load the bundle of the given name, from the specified path. The path may be to an executable or a shared library.
	 *
	 * @param bundleName the name of the bundle to load
	 * @param bundleFilePath the path to the bundle executable or library
	 */
	us::Bundle* Load(const std::string bundleName, const std::string bundleFilePath);
	/**
	 * Unloads the given bundle.
	 *
	 * @param bundle the bundle to unload
	 */
	void Unload(us::Bundle* bundle);
};

#endif /* BUNDLELOADER_H_ */
