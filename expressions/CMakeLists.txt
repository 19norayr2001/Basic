cmake_minimum_required(VERSION 3.16)

add_library(Expressions
        expression.h
        expression.cpp
		postfix.h
		postfix.cpp
        symbol.cpp symbol.h operation.cpp operation.h)