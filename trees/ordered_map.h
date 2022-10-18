#ifndef BASICS_ORDERED_MAP_H
#define BASICS_ORDERED_MAP_H

#include <treap.h>

template<typename Key, typename Value>
class ordered_map_node : public treap_node_base<ordered_map_node<Key, Value>> {
    using base_type = treap_node_base<ordered_map_node<Key, Value>>;
    using typename base_type::priority_type;
public:
    using key_type = Key;
    using value_type = std::pair<const Key, Value>;
public:
    explicit ordered_map_node(const value_type &value, priority_type priority = 0, ordered_map_node *left = nullptr,
                              ordered_map_node *right = nullptr)
            : base_type(priority, left, right), _value(value) {}

    const value_type *get_value_address() const { return std::addressof(_value); }

    value_type *get_value_address() { return std::addressof(_value); }

    const key_type &get_key() const { return _value.first; }

    const value_type &get_value() const {return _value; }

    value_type& get_value() {return _value;}

private:
    value_type _value;
};

template<typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
class ordered_map : public Treap<Key, ordered_map_node<Key, Value>, Compare, Allocator> {
private:
    using base_type = Treap<Key, ordered_map_node<Key, Value>, Compare, Allocator>;
public:
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;
public:
    using base_type::base_type;
    using typename base_type::size_type;
    using key_type = Key;
    using value_type = Value;

public:
    value_type& operator[](const key_type& key) {
        auto it = base_type::find(key);
        if (it == base_type::end()) {
            return base_type::emplace(key, value_type()).first->second;
        }
        return it->second;
    }

    const value_type& operator[](const key_type& key) const {
        return base_type::find(key)->second;
    }
};

#endif //BASICS_ORDERED_MAP_H
