cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "PC-club")
project(${PROJECT_NAME} LANGUAGES CXX C)

# GoogleTest requires at least C++17
# 20 version is required for some methods of std::unordered_set
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Targets
set(ALG_LIB_NAME "AlgorithmsLib")
set(SAMPLE "Sample")
set(GTESTS "Tests")

option(BUILD_GMOCK "Disable building gmock" OFF)
add_subdirectory(3rdparty/googletest)

add_subdirectory(include)
add_subdirectory(sample)
add_subdirectory(tests)

message(STATUS "Using compiler: " ${CMAKE_CXX_COMPILER_ID})
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})