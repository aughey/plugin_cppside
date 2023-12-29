#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add library for the source files
file(GLOB SOURCES "*.cpp")
add_library(your_project_lib ${SOURCES})
