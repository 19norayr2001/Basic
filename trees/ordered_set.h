#ifndef BASICS_ORDERED_SET_H
#define BASICS_ORDERED_SET_H

#include <treap.h>

namespace nstd {

template<typename Key>
class ordered_set_node : public treap_node_base<ordered_set_node<Key>> {
private:
    using base_type = treap_node_base<ordered_set_node<Key>>;
    using typename base_type::priority_type;
public:
    using key_type = Key;
    using value_type = Key;
public:
    explicit ordered_set_node(const key_type &key, priority_type priority = 0, ordered_set_node *left = nullptr,
                              ordered_set_node *right = nullptr)
            : base_type(priority, left, right), _key(key) {}

    const value_type *get_value_address() const { return std::addressof(_key); }

    value_type *get_value_address() { return std::addressof(_key); }

    const key_type &get_key() const { return _key; }

    const value_type &get_value() const { return _key; }

private:
    key_type _key;
};

template<typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
class ordered_set : public treap<ordered_set_node<const Key>, Compare, Allocator> {
    using base_type = treap<ordered_set_node<const Key>, Compare, Allocator>;
public:
    using key_type = Key;
    using value_type = Key;
    using typename base_type::key_compare;
    using typename base_type::allocator_type;
    using typename base_type::size_type;
public:
    using const_iterator = typename base_type::const_iterator;
    using iterator = const_iterator;
    using const_reverse_iterator = typename base_type::const_reverse_iterator;
    using reverse_iterator = const_reverse_iterator;
public:
    using base_type::base_type;

    ordered_set(std::initializer_list<key_type> il,
                const key_compare &comparator = key_compare(),
                const allocator_type &allocator = allocator_type())
            : base_type(comparator, allocator) {
        for (const auto &key: il) {
            base_type::emplace(key);
        }
    }

public:
    iterator find(const key_type &key) const {
        return base_type::find(key);
    }

    iterator begin() const { return base_type::cbegin(); }

    iterator end() const { return base_type::cend(); }

    reverse_iterator rbegin() const { return base_type::crbegin(); }

    reverse_iterator rend() const { return base_type::crend(); }
    };

} // namespace nstd

#endif //BASICS_ORDERED_SET_H
