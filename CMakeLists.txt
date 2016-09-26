cmake_minimum_required(VERSION 3.6)
project(xhooks)

set(GCC_COVERAGE_LINK_FLAGS "-lxcb -lX11 -lXau -lXext -lSM -lICE -lfreetype -lXrandr  -lXt -lXrandr -lXrender -lXdamage  -lxcb-randr -lxcb-xfixes -lxcb-shape -lxcb-shm -lxcb-sync -lxcb-render  -lxcb-glx -lXfixes -lXext -lX11-xcb -lX11 -lxcb -lXau -lXdmcp -lfreetype -lm -lz -lstdc++  -lSM -lICE")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(CMAKE_EXE_LINKER_FLAGS  "${GCC_COVERAGE_LINK_FLAGS}" )
set(SOURCE_FILES main.c)
add_executable(xhooks ${SOURCE_FILES})