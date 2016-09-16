cmake_minimum_required(VERSION 3.4)
project(NLPAssignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SpellCorrector.cpp SpellCorrector.h Distribution.cpp Distribution.h Transform.cpp Transform.h SpaceTransform.cpp SpaceTransform.h)
add_executable(NLPAssignment ${SOURCE_FILES})