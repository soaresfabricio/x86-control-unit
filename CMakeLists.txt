cmake_minimum_required(VERSION 2.8)
project(cpu)
set(NAME cpu)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3 -Wall")

file(GLOB MAIN main.cpp)
file(GLOB_RECURSE SOURCES ./src/*.cpp)
file(GLOB_RECURSE HEADERS ./include/*.hpp)

add_executable(
    ${NAME} 
    ${MAIN}
    ${SOURCES}
    ${HEADERS}
)