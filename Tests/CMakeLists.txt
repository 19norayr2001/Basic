cmake_minimum_required(VERSION 3.16)

add_executable(Basics linear_list_test.cpp sorting_test.cpp expressions_test.cpp polynomial_test.cpp)
add_test(NAME example_test COMMAND Basics)