# C++ Basics

Basics is a cross platform C++ library developed under `CMake`, where are implemented STL data structures, algorithms, etc.

## Linear lists

### Vector

Vector container has the most advanced implementation among linear lists.

This container provides

- `emplace back`, which uses perfect forwarding technique
- `emplace back`, `push_back`, `pop_back`, `reserve`, `swap`, `empty`, `size` public functions
- `strong exception safety`, `move semantics` for public functions
- possibility of using `custom allocators` 
- `iterator`, `reverse iterator`

Check out some usages of vector
```c++
// vector with polymorphic allocator
Vector<int, std::pmr::polymorphic_allocator<int>> vec;
// reserve memory for 100 elements
vec.reserve(100);
// add elements in vector
for(int i = 0; i < 10; ++i) {
    vec.push_back(i);
}
// using reverse iterators, print all vector elements in reverse order
for(auto it = vec.rbegin(); it != vec.rend(); ++it) {
    std::cout << *it << ' ';
}
```