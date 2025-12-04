cmake_minimum_required(VERSION 3.15)
project(aoc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Automatically find all Day directories
file(GLOB DAY_DIRS "${CMAKE_SOURCE_DIR}/day*")

foreach(DAY_DIR ${DAY_DIRS})
    add_subdirectory(${DAY_DIR})
endforeach()