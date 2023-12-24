# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.13)

# Project name
project(VanillaCake)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Add the -g flag for debug symbols
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")


# Add source files
set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/List/List.c
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/List/ListNode.c
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/DataObject/DataObject.c
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/Stack/Stack.c
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/Vector/Vector.c
    # Add other source files as needed
)

# Create a library for the main project source files
add_library(VanillaCakeLib ${SOURCE_FILES})

# Specify include directories explicitly
target_include_directories(VanillaCakeLib
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/AbstractDataTypes
    ${CMAKE_SOURCE_DIR}/include/AbstractDataTypes/DataObject
    ${CMAKE_SOURCE_DIR}/include/AbstractDataTypes/List
    ${CMAKE_SOURCE_DIR}/include/AbstractDataTypes/Stack
    ${CMAKE_SOURCE_DIR}/include/AbstractDataTypes/Vector
    # Add other subdirectories as needed
)

# Create the executable for the main project
add_executable(VanillaCake src/main.c)

if (WIN32)
    target_compile_options(VanillaCake PRIVATE /MT)
else()
    target_compile_options(VanillaCake PRIVATE -pthread)
endif()

# Link the library to the main executable
target_link_libraries(VanillaCake PRIVATE VanillaCakeLib)

# Include the tests subdirectory
add_subdirectory(tests)
