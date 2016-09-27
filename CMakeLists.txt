cmake_minimum_required(VERSION 3.6)
project(xhooks)

set(CMAKE_STATIC_LINKER_FLAGS "-lxcb")
#-lX11 -lXau -lXext -lSM -lICE -lfreetype -lXrandr  -lXt -lXrandr -lXrender -lXdamage  -lxcb-randr -lxcb-xfixes -lxcb-shape -lxcb-shm -lxcb-sync -lxcb-render  -lxcb-glx -lXfixes -lXext -lX11-xcb -lX11 -lxcb -lXau -lXdmcp -lfreetype -lm -lz -lstdc++  -lSM -lICE")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
#set(LINK_LIBRARIES  "${CMAKE_STATIC_LINKER_FLAGS}" )
set(SOURCE_FILES main.c)
add_executable(xhooks ${SOURCE_FILES})
target_link_libraries(xhooks ${CMAKE_STATIC_LINKER_FLAGS})
