#ifndef BASICS_ORDERED_SET_HPP
#define BASICS_ORDERED_SET_HPP

#include <treap.hpp>

namespace nstd {

template <typename Key>
class ordered_set_node : public treap_node_base<ordered_set_node<Key>> {
private:
    using base_type = treap_node_base<ordered_set_node<Key>>;
    using typename base_type::priority_type;
public:
    using key_type = const Key;
    using value_type = key_type;
    using raw_key_type = Key;
    using raw_value_type = Key;
public:
    explicit ordered_set_node(const key_type& key, priority_type priority = 0, ordered_set_node* left = nullptr,
                              ordered_set_node* right = nullptr)
            : base_type(priority, left, right), _key(key) {}

    const value_type* get_value_address() const { return std::addressof(_key); }

    value_type* get_value_address() { return std::addressof(_key); }

    const key_type& get_key() const { return _key; }

    const value_type& get_value() const { return _key; }

public:
    static const key_type& get_key(const value_type& value) { return value; }

private:
    key_type _key;
};

template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
class ordered_set : public treap<ordered_set_node<Key>, Compare, Allocator> {
    using base_type = treap<ordered_set_node<Key>, Compare, Allocator>;

public:
    using key_type = Key;
    using value_type = Key;
    using typename base_type::key_compare;
    using typename base_type::allocator_type;
    using typename base_type::size_type;

public:
    using const_iterator = typename base_type::const_iterator;
    using iterator = typename base_type::iterator;
    using const_reverse_iterator = typename base_type::const_reverse_iterator;
    using reverse_iterator = typename base_type::reverse_iterator;

public:
    using base_type::base_type;

    ordered_set(std::initializer_list<key_type> il,
                const key_compare& comparator = key_compare(),
                const allocator_type& allocator = allocator_type())
            : base_type(comparator, allocator) {
        for (const auto& key: il) {
            base_type::insert(key);
        }
    }
};

} // namespace nstd

#endif //BASICS_ORDERED_SET_HPP
