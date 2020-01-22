cmake_minimum_required(VERSION 2.6)

project(klasters) 

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

file(GLOB CPPS "*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})