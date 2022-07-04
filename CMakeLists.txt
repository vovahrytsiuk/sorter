cmake_minimum_required(VERSION 3.10)

# set the project name
project(sorter)

file(GLOB SOURCES src/*.cpp src/*.h)

# add the executable
add_executable(sorter ${SOURCES})