cmake_minimum_required(VERSION 3.14) # Ensure a compatible version
project(your_project_name VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Werror)

# # Add this to enable testing in your project
# option(BUILD_TESTING "Build the testing tree." OFF)
# if (DEFINED BUILD_TESTING)
#     add_subdirectory(tests)
#     enable_testing()
# endif()

# Add the executable
add_executable(your_project main.cpp)
# add your_project_lib to the executable
target_link_libraries(your_project PRIVATE your_project_lib)
target_link_libraries(your_project PRIVATE dl)

# Include directories
include_directories(include)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(dynamic_plugin)
