cmake_minimum_required(VERSION 3.6)
project(xhooks)

set(GCC_COVERAGE_LINK_FLAGS "-lxcb-image -lxcb-icccm -lxcb")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(CMAKE_EXE_LINKER_FLAGS  "${GCC_COVERAGE_LINK_FLAGS}" )
set(SOURCE_FILES main.c)
add_executable(xhooks ${SOURCE_FILES})