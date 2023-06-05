cmake_minimum_required(VERSION 3.20)

project(Character VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

include_directories(${CMAKE_SOURCE_DIR})

add_library(BaseLibrary
        base/config/build_config.h
        base/memory/aligned_memory.cc
        base/memory/aligned_memory.h
        base/time/time_delta.cc
        base/time/time_delta.h
        )

add_library(MediaLibrary
        media/base/audio_bus.cc
        media/base/audio_bus.h
        media/base/audio_constant.h
        media/base/audio_parameters.cc
        media/base/audio_parameters.h
        media/filters/ffmpeg_audio_decoder.cc
        media/filters/ffmpeg_audio_decoder.h
        )
target_link_libraries(MediaLibrary
        PRIVATE
        BaseLibrary
        ${CONAN_LIBS}
        )

# Media library unit test
enable_testing()

add_executable(MediaLibraryTest
        media/filters/ffmpeg_audio_decoder_test.cc
        )
target_link_libraries(MediaLibraryTest
        PRIVATE
        MediaLibrary
        ${CONAN_LIBS}
        )

include(GoogleTest)
gtest_discover_tests(MediaLibraryTest)

set(VIEW_SOURCES
        view/widgets/character_window.cc
        view/widgets/character_window.h
        view/widgets/waveform_widget.cc
        view/widgets/waveform_widget.h
        )

qt_add_executable(Character
        MANUAL_FINALIZATION
        main.cc
        ${VIEW_SOURCES}
        )

target_link_libraries(Character
        PRIVATE
        BaseLibrary
        MediaLibrary
        ${CONAN_LIBS}
        Qt${QT_VERSION_MAJOR}::Widgets
        )

qt_finalize_executable(Character)
