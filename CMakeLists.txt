cmake_minimum_required(VERSION 3.4)
project(NLPAssignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ffunction-sections -fdata-sections -Wl")

set(SOURCE_FILES main.cpp transforms/Transform.cpp transforms/SpaceTransform.cpp)

add_executable(NLPAssignment ${SOURCE_FILES})