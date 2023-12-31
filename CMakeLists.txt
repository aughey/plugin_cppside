cmake_minimum_required(VERSION 3.14) # Ensure a compatible version
project(sim_prototype_name VERSION 1.0 LANGUAGES CXX)

# Option to compile c++ 20
# Specify the C++ standard
if(DEFINED USE_CXX_20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

add_compile_options(-Wall -Wextra -Werror)

# # Add this to enable testing in your project
# option(BUILD_TESTING "Build the testing tree." OFF)
# if (DEFINED BUILD_TESTING)
#     add_subdirectory(tests)
#     enable_testing()
# endif()

# Add the executable
add_executable(sim_prototype main.cpp)
# add sim_prototype_lib to the executable
target_link_libraries(sim_prototype PRIVATE sim_prototype_lib)
target_link_libraries(sim_prototype PRIVATE dl)

# Include directories
include_directories(include)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(dynamic_plugin)
