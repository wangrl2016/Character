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
        media/base/audio_bus_test.cc
        media/filters/ffmpeg_audio_decoder_test.cc
        )
target_link_libraries(MediaLibraryTest
        PRIVATE
        MediaLibrary
        ${CONAN_LIBS}
        )

include(GoogleTest)
gtest_discover_tests(MediaLibraryTest)

add_subdirectory(third_party/JUCE)

set(JUCE_LIBRARY
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_dsp
        )

add_library(AudioGraphModule
        module/audio_graph/audio_bridge.cc
        module/audio_graph/audio_bridge.h
        module/audio_graph/audio_context.cc
        module/audio_graph/audio_context.h
        module/audio_graph/constant.h
        module/audio_graph/gain_node.cc
        module/audio_graph/gain_node.h
        module/audio_graph/metronome_node.cc
        module/audio_graph/metronome_node.h
        module/audio_graph/oscillator.cc
        module/audio_graph/oscillator.h
        module/audio_graph/oscillator_node.cc
        module/audio_graph/oscillator_node.h
        module/audio_graph/processor_base.h
        module/audio_graph/track.cc
        module/audio_graph/track.h
        )

target_link_libraries(AudioGraphModule
        ${JUCE_LIBRARY}
        )

set(VIEW_SOURCES
        core/math/constant.h
        ui/model/clip.cc
        ui/model/clip.h
        ui/model/instrument_track.cc
        ui/model/instrument_track.h
        ui/model/model.cc
        ui/model/model.h
        ui/model/note.cc
        ui/model/note.h
        ui/model/piano.cc
        ui/model/piano.h
        ui/model/song.cc
        ui/model/song.h
        ui/model/track.cc
        ui/model/track.h
        ui/view/widgets/main_window.cc
        ui/view/widgets/main_window.h
        ui/view/widgets/piano_view.cc
        ui/view/widgets/piano_view.h
        ui/view/widgets/resource_view.cc
        ui/view/widgets/resource_view.h
        ui/view/widgets/waveform_widget.cc
        ui/view/widgets/waveform_widget.h
        ui/view/widgets/widget_constant.h
        )

qt_add_executable(Character
        MANUAL_FINALIZATION
        main.cc
        res/application.qrc
        ${VIEW_SOURCES}
        )

target_link_libraries(Character
        PRIVATE
        AudioGraphModule
        BaseLibrary
        MediaLibrary
        ${CONAN_LIBS}
        ${JUCE_LIBRARY}
        Qt${QT_VERSION_MAJOR}::Widgets
        )

qt_finalize_executable(Character)
