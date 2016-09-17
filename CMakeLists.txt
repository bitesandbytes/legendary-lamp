cmake_minimum_required(VERSION 3.4)
project(NLPAssignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SpellCorrector.cpp SpellCorrector.h distributions/distribution.h transforms/Transform.cpp transforms/Transform.h transforms/SpaceTransform.cpp transforms/SpaceTransform.h)
add_executable(NLPAssignment ${SOURCE_FILES})