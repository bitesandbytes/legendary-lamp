cmake_minimum_required(VERSION 3.4)
project(NLPAssignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")

set(SOURCE_FILES main.cpp transforms/Transform.cpp transforms/SpaceTransform.cpp)

add_executable(NLPAssignment ${SOURCE_FILES})