cmake_minimum_required(VERSION 3.10)

set(PROJECT DiceRandomGenerator)

project(${PROJECT})
set(CMAKE_CXX_STANDARD 14)

include_directories(src)

set (HEADERS
    src/mersenne.h
    src/dicerandomgenerator.h)

set (SOURCES
    src/mersenne.cpp
    src/dicerandomgenerator.cpp
    src/main.cpp)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})
