# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.15)

# Project name
project(VanillaCake)

# Set C standard to C99
set(CMAKE_C_STANDARD 99)

# Add source files
set(SOURCE_FILES
    src/main.c
    src/List/ListNode.c
    src/DataContainer/DataContainer.c
    src/DataContainer/DataContainerTest.c
    # Add other source files as needed
)

# Specify include directories explicitly
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/DataContainer
    ${CMAKE_SOURCE_DIR}/include/List
    # Add other subdirectories as needed
)

# Create the executable
add_executable(VanillaCake ${SOURCE_FILES})
