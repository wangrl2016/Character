cmake_minimum_required(VERSION 3.20)
project(AudioGraph CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(AudioGraph hello.cc)
target_include_directories(AudioGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(AudioGraph PROPERTIES PUBLIC_HEADER "hello.h")
install(TARGETS AudioGraph)
