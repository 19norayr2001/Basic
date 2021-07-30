cmake_minimum_required(VERSION 3.20.2)

add_library(Iterators INTERFACE back_insert_iterator.h insert_iterator.h)
target_compile_features(Iterators INTERFACE cxx_std_17)