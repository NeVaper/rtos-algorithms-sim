cmake_minimum_required(VERSION 3.5.1)

set (CMAKE_CXX_STANDARD 11)

set(SIM rtos-algorithms-sim)

project(${SIM})

file(GLOB SRC src/*.cpp src/*.h)

add_executable(${SIM} ${SRC})