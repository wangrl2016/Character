cmake_minimum_required(VERSION 3.20)

project(BaseLibrary VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(BaseLibrary
        config/build_config.h
        files/file_path.cc
        files/file_path.h
        memory/aligned_memory.cc
        memory/aligned_memory.h
        time/time_delta.cc
        time/time_delta.h
        )
