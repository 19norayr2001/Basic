#ifndef BASICS_VECTOR_TREE_H
#define BASICS_VECTOR_TREE_H

#include <implicit_treap.h>

template<typename T, typename Allocator = std::allocator<T>>
using vector_tree = implicit_treap<T, Allocator>;

#endif //BASICS_VECTOR_TREE_H
