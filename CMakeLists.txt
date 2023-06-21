cmake_minimum_required(VERSION 3.20)

project(Character VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

list(APPEND CMAKE_PREFIX_PATH "/Users/admin/Qt/6.3.1/macos")
# set(CMAKE_TOOLCHAIN_FILE "cmake-build-debug/build/Debug/generators/conan_toolchain.cmake")

find_package(ZLIB REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(BaseLibrary
        base/files/file_path.cc
        base/memory/aligned_memory.cc
        base/time/time_delta.cc
        base/config/build_config.h
        base/files/file_path.h
        base/memory/aligned_memory.h
        base/time/time_delta.h
        )

add_subdirectory(third_party/JUCE)
add_subdirectory(third_party/portsmf)

set(JUCE_LIBRARY
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        )

add_library(AudioGraphModule STATIC
        module/audio_graph/audio_bridge.cc
        module/audio_graph/audio_bridge.h
        module/audio_graph/audio_context.cc
        module/audio_graph/audio_context.h
        module/audio_graph/constant.h
        module/audio_graph/gain_node.cc
        module/audio_graph/gain_node.h
        module/audio_graph/master_track.cc
        module/audio_graph/master_track.h
        module/audio_graph/metronome_node.cc
        module/audio_graph/metronome_node.h
        module/audio_graph/oscillator.cc
        module/audio_graph/oscillator.h
        module/audio_graph/oscillator_node.cc
        module/audio_graph/oscillator_node.h
        module/audio_graph/piano_node.cc
        module/audio_graph/piano_node.h
        module/audio_graph/processor_base.h
        module/audio_graph/time_stretch_node.cc
        module/audio_graph/time_stretch_node.h
        module/audio_graph/track.cc
        module/audio_graph/track.h
        )

target_link_libraries(AudioGraphModule
        PRIVATE
        ${JUCE_LIBRARY}
        ${CONAN_LIBS}
        )

set(VIEW_SOURCES
        app/dialog/about_dialog.cc
        app/dialog/about_dialog.h
        app/toolbar/top_tool_bar.cc
        app/toolbar/top_tool_bar.h
        app/main_window.cc
        app/main_window.h
        core/math/constant.h
        core/midi/midi.h
        core/midi/midi_event.h
        core/midi/midi_event_processor.h
        core/util/utility_function.h
#        ui/menu/about_dialog.cc
#        ui/menu/about_dialog.h
#        ui/model/clip.cc
#        ui/model/clip.h
#        ui/model/instrument_track.cc
#        ui/model/instrument_track.h
#        ui/model/midi_clip.cc
#        ui/model/midi_clip.h
#        ui/model/model.cc
#        ui/model/model.h
#        ui/model/note.cc
#        ui/model/note.h
#        ui/model/piano.cc
#        ui/model/piano.h
#        ui/model/song.cc
#        ui/model/song.h
#        ui/model/time_pos.cc
#        ui/model/time_pos.h
#        ui/model/track.cc
#        ui/model/track.h
#        ui/model/track_container.cc
#        ui/model/track_container.h
#        ui/plugin/import_filter.cc
#        ui/plugin/import_filter.h
#        ui/plugin/instrument.cc
#        ui/plugin/instrument.h
#        ui/plugin/midi_import.cc
#        ui/plugin/midi_import.h
#        ui/plugin/plugin.cc
#        ui/plugin/plugin.h
#        ui/view/setting/audio_device_selector.cc
#        ui/view/setting/audio_device_selector.h
#        ui/view/setting/device_combo_box.cc
#        ui/view/setting/device_combo_box.h
#        ui/view/setting/setting_widget.cc
#        ui/view/setting/setting_widget.h
#        ui/view/widget/clip_view.cc
#        ui/view/widget/clip_view.h
#        ui/view/widget/instrument_track_view.cc
#        ui/view/widget/instrument_track_view.h
#        ui/view/widget/main_window.cc
#        ui/view/widget/main_window.h
#        ui/view/widget/midi_clip_view.cc
#        ui/view/widget/midi_clip_view.h
#        ui/view/widget/model_view.cc
#        ui/view/widget/model_view.h
#        ui/view/widget/piano_view.cc
#        ui/view/widget/piano_view.h
#        ui/view/widget/resource_view.cc
#        ui/view/widget/resource_view.h
#        ui/view/widget/selectable_object.cc
#        ui/view/widget/selectable_object.h
#        ui/view/widget/track_view.cc
#        ui/view/widget/track_view.h
#        ui/view/widget/song_view.cc
#        ui/view/widget/song_view.h
#        ui/view/widget/time_line_widget.cc
#        ui/view/widget/time_line_widget.h
#        ui/view/widget/track_container_view.cc
#        ui/view/widget/track_container_view.h
#        ui/view/widget/track_content_widget.cc
#        ui/view/widget/track_content_widget.h
#        ui/view/widget/track_setting_widget.cc
#        ui/view/widget/track_setting_widget.h
#        # ui/view/widget/waveform_widget.cc
#        # ui/view/widget/waveform_widget.h
#        ui/view/widget/widget_constant.h
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
        PortSMF
        ${CONAN_LIBS}
        Qt${QT_VERSION_MAJOR}::Widgets
        )

qt_finalize_executable(Character)
