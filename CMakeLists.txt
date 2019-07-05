cmake_minimum_required(VERSION 3.14)
project(FS)

set(CMAKE_CXX_STANDARD 14)

link_directories(lib)

add_executable(FS FS.cpp)

target_link_libraries(FS libJiang.a)