cmake_minimum_required(VERSION 3.20.2)

#set project name
project(Basics)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(TEST_EXPRESSIONS "Use expression implementation" ON)
option(TEST_LINEAR_LISTS "Use linear lists implementation" ON)
option(TEST_POLYNOMIALS "Use polynomials implementation" ON)
option(TEST_SORTINGS "Use sorting algorithms implementation" ON)
option(TEST_TREES "Use trees implementation" ON)
option(TEST_ITERATORS "Use polynomials implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(BasicsConfig.h.in BasicsConfig.h)
						   
# if need to test, then add the Expressions library
if(TEST_EXPRESSIONS)
  add_subdirectory(Expressions)
  list(APPEND EXTRA_LIBS Expressions)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Expressions")
endif()

# if need to test, then add the LinearLists library
if(TEST_LINEAR_LISTS)
  add_subdirectory(LinearLists)
  list(APPEND EXTRA_LIBS LinearLists)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/LinearLists")
endif()

# if need to test, then add the Polynomials library
if(TEST_POLYNOMIALS)
  add_subdirectory(Polynomials)
  list(APPEND EXTRA_LIBS Polynomials)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Polynomials")
endif()

# if need to test, then add the Sortings library
if(TEST_SORTINGS)
  add_subdirectory(Sortings)
  list(APPEND EXTRA_LIBS Sortings)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Sortings")
endif()

# if need to test, then add the Trees library
if(TEST_TREES)
  add_subdirectory(Trees)
  list(APPEND EXTRA_LIBS Trees)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Trees")
endif()

# if need to test, then add the Iterators library
if(TEST_ITERATORS)
  add_subdirectory(Iterators)
  list(APPEND EXTRA_LIBS Iterators)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Iterators")
endif()

# add the executable
add_executable(Basics Main.cpp UnitTests.cpp UnitTests.h)

target_link_libraries(Basics PUBLIC ${EXTRA_LIBS})

# add the binary tree to the search path for include files
# so that we will find BasicsConfig.h
target_include_directories(Basics PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${EXTRA_INCLUDES}
                           )