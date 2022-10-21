#ifndef BASICS_VECTOR_TREE_HPP
#define BASICS_VECTOR_TREE_HPP

#include <implicit_treap.hpp>

namespace nstd {

template<typename T, typename Allocator = std::allocator<T>>
class vector_tree : public implicit_treap<T, Allocator> {
    using base_type = implicit_treap<T, Allocator>;

public:
    using typename base_type::value_type;
    using typename base_type::allocator_type;
    using typename base_type::size_type;

public:
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

public:
    using base_type::base_type;

    vector_tree(std::initializer_list<value_type> il,
                const allocator_type& allocator = allocator_type())
            : base_type(allocator) {
        for (const auto& value: il) {
            base_type::emplace_back(value);
        }
    }
};

} // namespace nstd

#endif //BASICS_VECTOR_TREE_HPP
