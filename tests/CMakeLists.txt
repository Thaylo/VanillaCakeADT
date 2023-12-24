# Add your test source files
set(TEST_FILES
    test_main.cpp
    test_DataObject.cpp
    test_ListNode.cpp
    test_List.cpp
    test_General_Helpers.cpp
    test_List_Helpers.cpp
    test_Stack.cpp
    test_Vector.cpp
    test_Vector_Helpers.cpp
    # Add other test files as needed
)

# Create the test executable
add_executable(unit_tests ${TEST_FILES})

# Link the library to the test executable
target_link_libraries(unit_tests PRIVATE VanillaCakeLib)

# Include Google Test headers
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include)



# Link against the Google Test library
if (WIN32)
    
    # Specific Flag (MT) for Microsoft Visual Studio's compiler
    target_compile_options(unit_tests PRIVATE /MT)
    # On Windows, use .lib files
    target_link_libraries(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party/googletest/build/lib/Release/gtest.lib)
    target_link_libraries(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party/googletest/build/lib/Release/gtest_main.lib)
    
else()
    target_compile_options(unit_tests PRIVATE -pthread) # Use appropriate flag for multithreading on Linux
    target_link_libraries(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party/googletest/build/lib/libgtest.a)
    target_link_libraries(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/third_party/googletest/build/lib/libgtest_main.a)
endif()

# Link against the source files
target_sources(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/DataObject/DataObject.c
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/List/List.c
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/List/ListNode.c
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/Stack/Stack.c
    ${CMAKE_SOURCE_DIR}/src/AbstractDataTypes/Vector/Vector.c

    # Add other source files as needed
)
