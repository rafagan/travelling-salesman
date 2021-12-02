cmake_minimum_required(VERSION 3.21)
project(travelling_salesman)

set(CMAKE_CXX_STANDARD 17)

#file(GLOB_RECURSE HEADERS src/*.h)
include_directories(src)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(travelling_salesman ${SOURCES} src/graph/Node.h src/math/math_util.h src/math/math_util.h src/graph/Node.cpp)
