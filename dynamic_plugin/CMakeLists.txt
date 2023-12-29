cmake_minimum_required(VERSION 3.10)

project(dynamic_plugin VERSION 1.0)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_library(dynamic_plugin SHARED dynamic_plugin.cpp)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

install(TARGETS dynamic_plugin DESTINATION lib)
