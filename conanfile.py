from conans import *
import subprocess

class usBundleLoaderConan(ConanFile):
    name = 'usBundleLoader'
    version = '0.1.0'
    settings = ['os', 'compiler', 'build_type', 'arch']
    generators = ['cmake']
    options = { 'BUILD_SHARED_LIBS': ['ON', 'OFF'] }
    default_options = 'BUILD_SHARED_LIBS=OFF'

    # Prefer 'exports' over 'source' as we may want to build off a particular branch
    # Can we assume running 'git ls-files' to be safe?
    exports = subprocess.check_output(['git', 'ls-files']).split()

    build_dir = 'build'

    def requirements(self):
        """ Declare here your project requirements or configure any of them """
        self.requires('CppMicroServices/3.0.0@azriel91/testing')
        self.requires('sl_cmake/0.1.0@azriel91/testing')
        self.requires('googletest/1.7.0@azriel91/stable-1')

    def config(self):
        cppmicroservices_options = self.options['CppMicroServices']
        setattr(cppmicroservices_options, 'US_BUILD_SHARED_LIBS', getattr(self.options, 'BUILD_SHARED_LIBS'))

    def build(self):
        option_defines = ' '.join("-D%s=%s" % (option, val) for (option, val) in self.options.iteritems())

        self.run("cmake . -B{build_dir} {defines}".format(build_dir=self.build_dir, defines=option_defines))
        self.run("cmake --build {build_dir}".format(build_dir=self.build_dir))

    def package(self):
        self.copy('*.h', dst='include', src='.')

        # Built artifacts
        lib_dir = "{build_dir}/lib".format(build_dir=self.build_dir)
        self.copy('*.so', dst='lib', src=lib_dir)
        self.copy('*.a', dst='lib', src=lib_dir)
        self.copy('*.lib', dst='lib', src=lib_dir)

    def package_info(self):
        self.cpp_info.libs = ['usBundleLoader']
