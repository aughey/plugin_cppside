cmake_minimum_required(VERSION 3.14) # Make sure this version is compatible with FetchContent

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)


# Include the GoogleTest library. This defines the gtest and gtest_main targets.
include(GoogleTest)

# Add your test executable
file(GLOB TEST_SOURCES "*.cpp")
add_executable(tests ${TEST_SOURCES})

# Link your test executable against gtest & gtest_main
target_link_libraries(tests gtest_main your_project_lib)

# Discover test cases
gtest_discover_tests(tests)