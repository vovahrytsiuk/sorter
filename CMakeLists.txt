cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 11)

# set the project name
project(sorter)

file(GLOB SOURCES src/*.cpp src/*.h src/*.cc)

# add the executable
add_executable(sorter ${SOURCES})