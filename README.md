# C++ Basics

`Basics` is a cross-platform C++ library based on `CMake`, where are implemented STL data structures, algorithms, etc. Library has unit tests for each module implemented using `gtest`.

Modules
- [Linear Lists](https://github.com/norayrbaghdasaryan/Basics#linear-lists)
  - [Vector](https://github.com/norayrbaghdasaryan/Basics#vector)
  - [Stack, Queue](https://github.com/norayrbaghdasaryan/Basics#stack-queue)
  - [Linked List](https://github.com/norayrbaghdasaryan/Basics#linked-list)
- [Trees](https://github.com/norayrbaghdasaryan/Basics#trees)
    - [Ordered Set, Ordered Map](https://github.com/norayrbaghdasaryan/Basics#ordered-set-ordered-map)
    - [Vector Tree](https://github.com/norayrbaghdasaryan/Basics#vector-tree)
    - [Binary Search Tree](https://github.com/norayrbaghdasaryan/Basics#binary-search-tree)
    - [Red Black Tree](https://github.com/norayrbaghdasaryan/Basics#red-black-tree)
    - [Priority Queue](https://github.com/norayrbaghdasaryan/Basics#priority-queue)
- [Smart Pointers](https://github.com/norayrbaghdasaryan/Basics#smart-pointers)
    - [Unique Pointer](https://github.com/norayrbaghdasaryan/Basics#unique-pointer)
    - [Shared Pointer](https://github.com/norayrbaghdasaryan/Basics#shared-pointer)
- [Sorting Algorithms](https://github.com/norayrbaghdasaryan/Basics#sorting-algorithms)

## Linear lists

### Vector

`nstd::vector` container has the most advanced implementation among linear lists.

This container provides

- `iterator`, `reverse iterator`
- possibility of using `custom allocators`
- public functions using `move semantics` and `perfect forwarding`
- `strong exception safety` guarantee for interface
- `emplace back`, `push_back` back insertion functions
- `pop_back` back erasure function
- `reserve`, `swap`, `empty`, `size` functions

Check out some usages of vector
```c++
// vector with polymorphic allocator
nstd::vector<int, std::pmr::polymorphic_allocator<int>> vec;
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

`nstd::stack` and `nstd::queue` are implemented as adapter containers, by default they are using std::deque

Their interface consist of several functions

- `push`, `pop`, `top`, `empty`, `size`

Here are some usages
```c++
// use stack based on deque
nstd::stack<char> st;
// use queue based on linked list
nstd::queue<char, std::list<char>> q;
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

### Linked List

Linked list container in this library is `not template` unlike the others and is not providing API for read operations from list (in other words this implementation is useless for any purposes but educational)

Provides

- `push_back`, `push_front`, `pop_back`, `pop_front`, `insert`, `erase` public functions
- Soon there will be added `iterator` and `template` parameter support

## Trees

### Ordered Set, Ordered Map

`nstd::ordered_set` and `nstd::ordered_map` are class based on `treap` data structure. 
These classes provide all the functionality, that are providing `std::set` and `std::map`. 
Lo and behold, they are ordered, so we can find order of any element in `O (log size)` complexity. 
This fact gives a very huge advantage under STL associative containers. These containers allow `erase_key_interval`, `erase_interval` operations in `O (interval_lenght + log size)` complexity. 
Nevertheless, single insertion and erasure operations are a little slower than STL ones.

These containers provide

- `iterator`, `reverse iterator`
- possibility of using `custom allocators`
- public functions using `move semantics` and `perfect forwarding`
- `weak exception safety` in case of comparison operation throw exception while insertion and erasure functions 
- Interval erasure functions working in `O (interval_size + log container_size)`
- `insert`, `emplace` insertion functions
- `erase_key` key erasure function 
- `erase_key_interval`, `erase_key_interval_with_end` key interval erasure functions
- `erase` iterator and iterator interval erasure functions
- `erase_index` index erasure function
- `erase_interval` index interval erasure function
- `key_of_order`, `order_of_key` functions working in `O (log size)` complexity
- `find`, `contains`, `lower_bound`, `upper_bound` particular key searching functions
- `swap`, `size`, `empty`, `clear` functions

Check out some usages of nstd ordered containers
```c++
nstd::ordered_set<int, std::greater<>> st {10, 7, 5, 4, 1, -1, -8};
size_t order = st.order_of_key(4);                 // order will be 3
int key = st.key_of_order(3);                      // key will be 4
st.erase_interval(st.begin() + 1, st.begin() + 3); // erase from set [1, 3) indexes
// here st = {10, 4, 1, -1, -8}

nstd::ordered_map<int, int> mp { {1, 2}, {4, 4}, {5, 6}, {10, -7}, {15, 6}};
size_t order = st.order_of_key(4);     // order will be 1
int key = st.key_of_order(1);          // key will be 4
mp.erase_key_interval_with_end(4, 10); // erases from map keys between [4, 10] interval
// here mp = { {1, 2}, {15, 6} }
```

### Vector Tree

`nstd::vector_tree` is a data structure modeled like `std::vector`, but based on `implicit treap`.
This class provides `std::vector`'s functionality as well.
The best part is that this structure can do a lot more than `std::vector`. It inserts and erases elements on any index at `O (log size)`. 
`nstd::vector_tree` can switch intervals in `O (log size)` complexity (notice that this complexity does not depend on interval sizes), which is amazing. 
This demon can even shift content (take a look at usages).
The only weakness under `std::vector` is that `push_back` and `pop_back` are also working in `O (log size)` complexity.

This container provides

- `iterator`, `reverse iterator`
- possibility of using `custom allocators`
- public functions using `move semantics` and `perfect forwarding`
- `strong exception safety` guarantee for interface
- Interval erasure functions working in `O (interval_size + log container_size)`
- `insert`, `emplace` insertion functions
- `push_back`, `emplace_back` back insertion functions
- `push_front`, `emplace_front` front insertion functions
- `erase` iterator and iterator interval erasure functions
- `erase_index` index erasure function
- `erase_interval` index interval erasure function
- `pop_back` back erasure function
- `pop_front` front erasure function
- `exchange_intervals`, `move_interval_to_index` interval move and swap functions
- `shift`, `shift_interval` clockwise shift functions
- `reverse_shift`, `reverse_shift_interval` counterclockwise shift functions
- `operator <<=`, `operator >>=` shift operators
- `swap`, `size`, `empty`, `clear` functions

Here are usages of nstd vector tree
```c++
nstd::vector_tree<int> vec {1, 6};
vec.insert(vec.begin() + 1, {2, 3, 4, 5});   // vec = {1, 2, 3, 4, 5, 6}
// clockwise shift vector 2 times
vec.shift(2);                                // vec = {5, 6, 1, 2, 3, 4}
// counterclockwise shift vector 3 times
vec <<= 3;                                   // vec = {2, 3, 4, 5, 6, 1}
// add 0 at vector front
vec.push_front(0);                           // vec = {0, 2, 3, 4, 5, 6, 1}
// exchange [1, 3) and [4, 7) vector intervals
vec.exchange_intervals(vec.begin() + 1, vec.begin() + 3,
                       vec.begin() + 4, vec.end());
                                             // vec = {0, 5, 6, 1, 4, 2, 3}
// move [0, 4) interval to the end of vector
vec.move_interval_to_index(vec.begin(), vec.begin() + 4, vec.end());
                                             // vec = {4, 2, 3, 0, 5, 6, 1}
// erase [2, 6) interval of the vector
vec.erase(vec.begin() + 2, vec.begin() + 6); // vec = {4, 2, 1}

for (int elem : vec) {
    std::cout << elem <<' ';                 // prints 4 2 1
}
```

### Binary Search Tree

This container is implemented as non-balanced binary search tree and gives following functionality

- `insert`
- `remove`
- `find`

All these functions complexity is `O(h)`, where `h` is the height of the tree

### Red Black Tree
`RBTree` extends from `BinarySearchTree` and provides same interface as `BinarySearchTree`. But through his balance, this container guarantees `O(log n)` complexity for his functions.

### Priority Queue

Priority Queue based on heap data structure, provides following API

- `top`, gives top element
- `insert`, inserts element in priority queue
- `pop`, removes top element from priority queue

## Smart Pointers

### Unique Pointer

Smart pointer providing unique ownership of memory resource. Ownership transfers from one to another with `std::move`

Usage.
```c++
// get pointer ownership
nstd::unique_ptr<int> ptr(new int());
// pass pointer ownership to another smart pointer
const nstd::unique_ptr<int> moved(std::move(ptr));
// get raw pointer
int* ptr = moved.get();
```

### Shared Pointer

Smart pointer providing shared ownership of memory resource. Ownership counter type is `std::atomic<int>` and provides thread safety.

Usage.
```c++
// create one shared ptr
nstd::shared_ptr<int> ptr(new int());
// create another shared ptr and share ownership with first one
nstd::shared_ptr<int> ptr2(ptr);
// now they are pointing at the same data
assert(ptr.get() == ptr2.get());
```

Soon there will be added `make_unique`, `make_shared` functions support in order to use benefits of `control block`.

### Weak Pointer

Not implemented yet.

## Sorting Algorithms

In this module, there are implemented several sorting algorithms

- `Bubble sort`
- `Insertion sort`
- `Selection sort`
- `Quick sort`
- `Radix sort`
- `Heap sort`
- `Merge sort`
