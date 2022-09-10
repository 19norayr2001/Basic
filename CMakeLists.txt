cmake_minimum_required(VERSION 3.16)

#set project name
project(Basics)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(TEST_EXPRESSIONS "Test expressions library" ON)
option(TEST_LINEAR_LISTS "Test linear lists library" ON)
option(TEST_POLYNOMIALS "Test polynomials library" ON)
option(TEST_SORTINGS "Test sorting algorithms library" ON)
option(TEST_TREES "Test trees library" ON)
option(TEST_ITERATORS "Test polynomials library" ON)
option(TEST_SMART_POINTERS "Test smart pointers library" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(basics_config.h.in BasicsConfig.h)

add_subdirectory(expressions)
list(APPEND EXTRA_LIBS Expressions)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/expressions")

add_subdirectory(linear_lists)
list(APPEND EXTRA_LIBS LinearLists)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/linear_lists")

add_subdirectory(polynomials)
list(APPEND EXTRA_LIBS Polynomials)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/polynomials")

add_subdirectory(sortings)
list(APPEND EXTRA_LIBS Sortings)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/sortings")

add_subdirectory(trees)
list(APPEND EXTRA_LIBS Trees)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/trees")

add_subdirectory(iterators)
list(APPEND EXTRA_LIBS Iterators)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/iterators")

add_subdirectory(smart_pointers)
list(APPEND EXTRA_LIBS SmartPointers)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/smart_pointers")

add_subdirectory(dependencies EXCLUDE_FROM_ALL)

add_subdirectory(tests)

target_link_libraries(Basics gtest_main ${EXTRA_LIBS})

# add the binary tree to the search path for include files
# so that we will find BasicsConfig.h
target_include_directories(Basics PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${EXTRA_INCLUDES}
                           )

