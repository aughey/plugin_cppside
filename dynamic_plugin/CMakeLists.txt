cmake_minimum_required(VERSION 3.10)

project(dynamic_plugin VERSION 1.0)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

file(GLOB SOURCES "*.cpp")

add_library(dynamic_plugin SHARED ${SOURCES})
# link to libplugin_rustside.a in the root of source
target_link_libraries(dynamic_plugin ${CMAKE_SOURCE_DIR}/libplugin_rustside.a)

# link to pthread
target_link_libraries(dynamic_plugin pthread)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

install(TARGETS dynamic_plugin DESTINATION lib)
