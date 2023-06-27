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
        app/gui/dialog/about_dialog.cc
        app/gui/dialog/about_dialog.h
        app/gui/style/color_constant.h
        app/gui/tab/bottom_tab_widget.cc
        app/gui/tab/bottom_tab_widget.h
        app/gui/tab/right_tab_widget.cc
        app/gui/tab/right_tab_widget.h
        app/gui/tab/left_tab_widget.cc
        app/gui/tab/left_tab_widget.h
        app/gui/tab/tab_widget.cc
        app/gui/tab/tab_widget.h
        app/gui/toolbar/middle_tool_bar.cc
        app/gui/toolbar/middle_tool_bar.h
        app/gui/toolbar/status_bar.cc
        app/gui/toolbar/status_bar.h
        app/gui/toolbar/top_tool_bar.cc
        app/gui/toolbar/top_tool_bar.h
        app/gui/widget/instrument/instrument_widget.cc
        app/gui/widget/instrument/instrument_widget.h
        app/gui/widget/instrument/piano.cc
        app/gui/widget/instrument/piano.h
        app/gui/widget/instrument/piano_roll.cc
        app/gui/widget/instrument/piano_roll.h
        app/gui/widget/timeline_widget.cc
        app/gui/widget/timeline_widget.h
        app/gui/widget/track_content_widget.cc
        app/gui/widget/track_content_widget.h
        app/gui/widget/track_delegate.cc
        app/gui/widget/track_delegate.h
        app/gui/widget/track_setting_widget.cc
        app/gui/widget/track_setting_widget.h
        app/gui/main_window.cc
        app/gui/main_window.h
        app/model/clip/clip.cc
        app/model/clip/clip.h
        app/model/music/note.cc
        app/model/music/note.h
        app/model/track/track.cc
        app/model/track/track.h
        app/model/play_progress_model.cc
        app/model/play_progress_model.h
        app/model/project_model.cc
        app/model/project_model.h
        app/model/track_container.cc
        app/model/track_container.h
        app/plugin/import_filter.cc
        app/plugin/import_filter.h
        app/plugin/midi_import.cc
        app/plugin/midi_import.h
        app/plugin/plugin.cc
        app/plugin/plugin.h
        app/presenter/play_progress_presenter.cc
        app/presenter/play_progress_presenter.h
        app/presenter/play_progress_subscriber.h
        app/presenter/play_progress_view.cc
        app/presenter/play_progress_view.h
        core/math/music_constant.h
        core/midi/midi.h
        core/midi/midi_event.h
        core/midi/midi_event_processor.h
        core/util/utility_function.h
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
