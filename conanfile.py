from conan import ConanFile


class CompressorRecipe(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'CMakeToolchain', 'CMakeDeps'

    default_options = {
        'ffmpeg/*:with_libiconv': False,
    }

    def requirements(self):
        self.requires('ffmpeg/5.0')
        self.requires('gtest/1.13.0')
        self.requires('glog/0.5.0')
        self.requires('protobuf/3.21.4')
        self.requires('zlib/1.2.13')

    # def build_requirements(self):
    #     self.tool_requires("cmake/3.22.6")
