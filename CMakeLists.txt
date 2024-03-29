cmake_minimum_required(VERSION 3.20)

project(Character VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
configure_file(app/config/user_config.h.in config/user_config.h)

# Proto file generate

if (WIN32)
    set(_GRPC_CPP_PLUGIN_EXECUTABLE ${CONAN_BIN_DIRS_GRPC}/grpc_cpp_plugin.exe)
else ()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE ${CONAN_BIN_DIRS_GRPC}/grpc_cpp_plugin)
endif ()

set(_PROTOBUF_PROTOC ${CONAN_BIN_DIRS_PROTOBUF}/protoc)
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app/project/proto)

set(OUT_DIR ${PROTO_DIR}/generated)
if (NOT EXISTS ${OUT_DIR})
    file(MAKE_DIRECTORY ${OUT_DIR})
endif ()

FILE(GLOB PROTO_FILES "${PROTO_DIR}/*.proto")

FOREACH (PROTO_FILE_PATH ${PROTO_FILES})
    execute_process(
            COMMAND ${_PROTOBUF_PROTOC}
            --grpc_out=${OUT_DIR}
            -I=${PROTO_DIR}
            --cpp_out=${OUT_DIR}
            --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE}
            ${PROTO_FILE_PATH}
    )
ENDFOREACH ()

# Proto file generate end

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

add_subdirectory(app)
add_subdirectory(base)
add_subdirectory(core)
add_subdirectory(media)
add_subdirectory(module)
add_subdirectory(third_party)

add_subdirectory(third_party/JUCE)
add_subdirectory(third_party/portsmf)

add_library(BaseLibrary STATIC ${BASE_LIBRARY_SOURCES})
target_link_libraries(BaseLibrary ${CONAN_LIBS})

add_library(MediaLibrary STATIC ${MEDIA_LIBRARY_SOURCES})
target_link_libraries(MediaLibrary PRIVATE BaseLibrary ${CONAN_LIBS})

add_library(ThirdPartyLibrary ${THIRD_PARTY_SOURCES})

# Media library unit test
enable_testing()

add_executable(BaseLibraryTest ${BASE_LIBRARY_TEST_SOURCES})
target_link_libraries(BaseLibraryTest PRIVATE BaseLibrary ThirdPartyLibrary ${CONAN_LIBS})

add_executable(MediaLibraryTest ${MEDIA_LIBRARY_TEST_SOURCES})
target_link_libraries(MediaLibraryTest PRIVATE BaseLibrary MediaLibrary ThirdPartyLibrary ${CONAN_LIBS})

include(GoogleTest)
gtest_discover_tests(BaseLibraryTest)
gtest_discover_tests(MediaLibraryTest)
# Media library test end

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

add_library(AudioGraphModule STATIC ${AUDIO_GRAPH_SOURCES})
target_link_libraries(AudioGraphModule PRIVATE ${JUCE_LIBRARY} ${CONAN_LIBS})

qt_add_executable(Character
        MANUAL_FINALIZATION
        main.cc
        res/application.qrc
        ${APP_SOURCES}
        ${CORE_SOURCES}
        )

target_link_libraries(Character
        PRIVATE
        AudioGraphModule
        BaseLibrary
        MediaLibrary
        ThirdPartyLibrary
        PortSMF
        ${CONAN_LIBS}
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
        )

qt_finalize_executable(Character)

# Image processing tool
add_subdirectory(tools)

qt_add_executable(CoverEditor
        MANUAL_FINALIZATION
        res/application.qrc
        ${COVER_EDITOR_SOURCES}
        )

target_link_libraries(CoverEditor
        PRIVATE
        BaseLibrary
        MediaLibrary
        ThirdPartyLibrary
        ${CONAN_LIBS}
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        )
