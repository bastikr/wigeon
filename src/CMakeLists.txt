cmake_minimum_required(VERSION 3.2)

project(robotworld)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall")

include_directories(../include)

add_subdirectory(rotations)

enable_testing()
add_subdirectory(tests)
