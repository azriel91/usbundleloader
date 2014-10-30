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

#include "BundleLoader.h"

BundleLoader::BundleLoader() {
}

BundleLoader::~BundleLoader() {
}

void BundleLoader::load(const std::string libraryPath) {
	std::map<const std::string, SharedLibrary>::const_iterator libIter = this->libraryHandles.find(libraryPath);

	if (libIter != this->libraryHandles.end()) {
		SharedLibrary libHandle = libIter->second;
		libHandle.Load();
	} else {
		SharedLibrary libHandle(libraryPath);
		libHandle.Load();
		this->libraryHandles.insert(std::make_pair(libraryPath, libHandle));
	}
}

void BundleLoader::unload(const long int id) {
	Module* const module = ModuleRegistry::GetModule(id);
	if (module) {
		std::map<std::string, SharedLibrary>::iterator libIter =
				this->libraryHandles.find(module->GetLocation());
		if (libIter == this->libraryHandles.end()) {
			std::cout << "Info: Unloading not possible. The module was loaded by a dependent module." << std::endl;
		} else {
			libIter->second.Unload();

			// Check if it has really been unloaded
			if (module->IsLoaded()) {
				throw std::logic_error("Info: The module is still referenced by another loaded module. It will be unloaded when all dependent modules are unloaded.");
			}
		}
	} else {
		char idString[64];
		std::sprintf(idString, "%ld", id);
		throw std::invalid_argument(std::string("Error: unknown bundle id: ") + idString);
	}
}
