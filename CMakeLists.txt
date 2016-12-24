cmake_minimum_required(VERSION 2.8)

project(Log)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Bin)

add_subdirectory(Core)
add_subdirectory(Example)
add_subdirectory(Log)