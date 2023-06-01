cmake_minimum_required(VERSION 3.20)

project(Character VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(base)
add_subdirectory(media)
add_subdirectory(third_party)
add_subdirectory(view)

add_executable(Character main.cc)
