# C++ Basics

Basics is a cross platform C++ library developed under `CMake`, where are implemented STL data structures, algorithms, etc. and is created for educational purposes 

## Linear lists

### Vector

Vector container has the most advanced implementation among linear lists.

This container provides

- `emplace back`, which uses perfect forwarding technique
- `emplace back`, `push_back`, `pop_back`, `reserve`, `swap`, `empty`, `size` public functions
- `strong exception safety`, `move semantics` for public functions
- possibility of using `custom allocators` 
- `iterator`, `reverse iterator`