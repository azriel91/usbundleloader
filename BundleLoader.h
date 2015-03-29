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

#include <azriel/cppmicroservices/core/include/usConfig.h>

#if defined(US_PLATFORM_POSIX)
	#include <dlfcn.h>
	#define DLL_EXPORT
#elif defined(US_PLATFORM_WINDOWS)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
	#include <strsafe.h>
	#define DLL_EXPORT __declspec(dllexport)
#else
	#error Unsupported platform
#endif

#include <map>
#include <string>
#include <cstdio>
#include <stdexcept>

#include <azriel/cppmicroservices/core/include/usModule.h>
#include <azriel/cppmicroservices/core/include/usModuleRegistry.h>
#include <azriel/cppmicroservices/core/include/usSharedLibrary.h>

US_USE_NAMESPACE

class DLL_EXPORT BundleLoader {
private:
	/**
	 * module path -> lib handle
	 *
	 * This has to be a pointer to allow the shared library (.lib) descriptors to be built on windows.
	 * See http://forum.biicode.com/t/solved-lib-file-not-generated-for-test-dependency/358
	 */
	std::map<const std::string, SharedLibrary>* libraryHandles;

public:
	BundleLoader();
	virtual ~BundleLoader();

	/**
	 * Load the bundle for the given shared library.
	 *
	 * @param libraryPath the path to the bundle library
	 */
	void load(const std::string libraryPath);
	/**
	 * Unload the bundle for the given bundle id.
	 *
	 * @param id the id of the bundle to unload
	 */
	void unload(const long int id);
};

#endif /* BUNDLELOADER_H_ */
