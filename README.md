# C++ Basics

`Basics` is a cross platform C++ library based on `CMake`, where are implemented STL data structures, algorithms, etc. Library has tests for each unit implemented using `gtest`

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

### Stack, Queue

Stack and Queue are implemented as adapter containers, by default they are using std::deque

They provide

- `push`, `pop`, `top`, `empty`, `size` public functions

Here are some usages
```c++
// use stack based on deque
Stack<char> st;
// use queue based on linked list
Queue<char, std::list<char>> q;
// push some elements in stack and queue
for(char ch = 'a'; ch <= 'z'; ++ch) {
    st.push(ch);
    q.push(ch);
}
// print stack and queue elements
while(!st.empty() && !q.empty()) {
    std::cout << st.top() << ' ' << q.front() << std::endl;
}
```

### Linked list

Linked list container in this library is `not template` like the others and is not providing API for read operations from list (in other words this implementation is useless for any purposes but educational)

Provides

- `push_back`, `push_front`, `pop_back`, `pop_front`, `insert`, `erase` public functions
- Soon there will be added `iterator` and `template` parameter support

## Smart pointers

### Unique pointer

Smart pointer providing unique ownership of memory resource. Ownership transfers from one to another with `std::move`

Usage.
```c++
// get pointer ownership
UniquePtr<int> ptr(new int());
// pass pointer ownership to another smart pointer
const UniquePtr<int> moved(std::move(ptr));
// get raw pointer
int* ptr = moved.get();
```

### Shared pointer

Smart pointer providing shared ownership of memory resource. Ownership counter type is `std::atomic<int>` and provides thread safety.

Usage.
```c++
// create one shared ptr
SharedPtr<int> ptr(new int());
// create another shared ptr and share ownership with first one
SharedPtr<int> ptr2(ptr);
// now they are pointing at the same data
assert(ptr.get() == ptr2.get());
```

Soon there will be added `makeUnique`, `makeShared` functions support in order to use benefits of `control block`.

### Weak Pointer

Not implemented yet.

## Trees

### Binary Search Tree

This container is implemented as non-balanced binary search tree and gives following functionality

- `insert`
- `remove`
- `find`

All these functions complexity is `O(h)`, where `h` is the height of the tree

### Red Black Tree
`RBTree` extends from `BinarySearchTree` and provides same interface as `BinarySearchTree`. But through his balance, this container guarantees `O(log n)` complexity for his functions.

### Priority Queue

Priority Queue based on heap providing following API

- `top`, gives top element
- `insert`, inserts element in priority queue
- `pop`, removes top element from priority queue

## Sorting Algorithms

In this module, there are implemented several sorting algorithms

- `Bubble sort`
- `Insertion sort`
- `Selection sort`
- `Quick sort`
- `Radix sort`
- `Heap sort`
- `Merge sort`