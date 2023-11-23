# Add your test source files
set(TEST_FILES
    test_main.cpp
    test_DataContainer.cpp
    # Add other test files as needed
)

# Create the test executable
add_executable(unit_tests ${TEST_FILES})

# Link the library to the test executable
target_link_libraries(unit_tests PRIVATE VanillaCakeLib)

# Include Google Test headers
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include)

# Link against the Google Test library
target_link_libraries(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party/googletest/build/lib/libgtest.a)
target_link_libraries(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party/googletest/build/lib/libgtest_main.a)

# Link against the source files
target_sources(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/DataContainer/DataContainer.c
    # Add other source files as needed
)
