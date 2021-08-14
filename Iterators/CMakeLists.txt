cmake_minimum_required(VERSION 3.16)

add_library(Iterators INTERFACE)
target_compile_features(Iterators INTERFACE cxx_std_17)