cmake_minimum_required(VERSION 2.6)

project(klasters) 

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c++11")

file(GLOB CPPS "${PROJECT_SOURCE_DIR}/klasters/*.cpp")
include_directories(${PROJECT_SOURCE_DIR}/klasters)

add_executable(${PROJECT_NAME} ${CPPS})

if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)