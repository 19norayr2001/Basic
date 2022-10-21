cmake_minimum_required(VERSION 3.16)

add_library(Expressions
        expression.hpp
        expression.cpp
		postfix.hpp
		postfix.cpp
        symbol.cpp symbol.hpp operation.cpp operation.hpp)