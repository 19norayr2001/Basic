cmake_minimum_required(VERSION 3.20.2)

add_library(Polynomials INTERFACE DividedByZeroException.h Field.h Polynomial.h)
target_compile_features(Polynomials INTERFACE cxx_std_11)