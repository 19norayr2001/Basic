cmake_minimum_required(VERSION 3.16)

include(GoogleTest)

# if need to test, then add the expressions test sources
if(TEST_EXPRESSIONS)
    list(APPEND TESTS_SOURCES expressions_test.cpp)
endif()

# if need to test, then add the linear_lists test sources
if(TEST_LINEAR_LISTS)
    list(APPEND TESTS_SOURCES linear_list_test.cpp)
endif()

# if need to test, then add the polynomials test sources
if(TEST_POLYNOMIALS)
    list(APPEND TESTS_SOURCES polynomial_test.cpp)
endif()

# if need to test, then add the sortings test sources
if(TEST_SORTINGS)
    list(APPEND TESTS_SOURCES sorting_test.cpp)
endif()

# if need to test, then add the trees test sources
if(TEST_TREES)
endif()

# if need to test, then add the iterators test sources
if(TEST_ITERATORS)
    list(APPEND TESTS_SOURCES iterators_test.cpp)
endif()

# if need to test, then add the smart pointers test sources
if(TEST_SMART_POINTERS)
    list(APPEND TESTS_SOURCES smart_pointers_test.cpp)
endif()

add_executable(Basics ${TESTS_SOURCES})

gtest_add_tests(
        TARGET Basics
)