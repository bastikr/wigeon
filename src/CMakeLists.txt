cmake_minimum_required(VERSION 3.2)

project(robotworld)

include_directories(../include)

add_subdirectory(rotations)

enable_testing()
add_subdirectory(tests)
