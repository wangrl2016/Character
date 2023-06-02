cmake_minimum_required(VERSION 3.20)

project(Character VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_SOURCE_DIR})

add_library(MediaLibrary
        media/base/audio_parameters.cc
        media/base/audio_parameters.h
        media/filters/ffmpeg_audio_decoder.cc
        media/filters/ffmpeg_audio_decoder.h
)

qt_add_executable(Character
        MANUAL_FINALIZATION
        main.cc
        )

target_link_libraries(Character
        ${MediaLibrary}
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        )

qt_finalize_executable(Character)
