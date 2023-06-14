cmake_minimum_required(VERSION 3.20)

project(BaseLibrary VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MediaLibrary
        base/audio_bus.cc
        base/audio_bus.h
        base/audio_constant.h
        base/audio_parameters.cc
        base/audio_parameters.h
        filters/ffmpeg_audio_decoder.cc
        filters/ffmpeg_audio_decoder.h
        filters/ffmpeg_audio_encoder.cc
        filters/ffmpeg_audio_encoder.h
        )
target_link_libraries(MediaLibrary
        PRIVATE
        BaseLibrary
        ${CONAN_LIBS}
        )

# Media library unit test
enable_testing()

add_executable(MediaLibraryTest
        base/audio_bus_test.cc
        filters/ffmpeg_audio_decoder_test.cc
        )
target_link_libraries(MediaLibraryTest
        PRIVATE
        MediaLibrary
        ${CONAN_LIBS}
        )

include(GoogleTest)
gtest_discover_tests(MediaLibraryTest)
