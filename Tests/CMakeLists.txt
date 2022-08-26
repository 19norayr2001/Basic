cmake_minimum_required(VERSION 3.16)

include(GoogleTest)

# if need to test, then add the expressions library
if(TEST_EXPRESSIONS)
    list(APPEND TESTS_SOURCES expressions_test.cpp)
endif()

# if need to test, then add the linear_lists library
if(TEST_LINEAR_LISTS)
    list(APPEND TESTS_SOURCES linear_list_test.cpp)
endif()

# if need to test, then add the Polynomials library
if(TEST_POLYNOMIALS)
    list(APPEND TESTS_SOURCES polynomial_test.cpp)
endif()

# if need to test, then add the Sortings library
if(TEST_SORTINGS)
    list(APPEND TESTS_SOURCES sorting_test.cpp)
endif()

# if need to test, then add the Trees library
if(TEST_TREES)
endif()

# if need to test, then add the iterators library
if(TEST_ITERATORS)
    list(APPEND TESTS_SOURCES Iterators_test.cpp)
endif()

add_executable(Basics ${TESTS_SOURCES})

gtest_add_tests(
        TARGET Basics
)