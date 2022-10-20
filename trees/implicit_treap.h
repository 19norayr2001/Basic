#ifndef BASICS_IMPLICIT_TREAP_BASE_H
#define BASICS_IMPLICIT_TREAP_BASE_H

#include <utility>
#include <treap_base.h>

template<typename T>
class implicit_treap_node : public treap_node_base<implicit_treap_node<T>> {
private:
    using base_type = treap_node_base<implicit_treap_node<T>>;
    using typename base_type::priority_type;
public:
    using key_type = size_t;
    using value_type = T;
public:
    explicit implicit_treap_node(const value_type &value, priority_type priority = 0,
                                 implicit_treap_node *left = nullptr,
                                 implicit_treap_node *right = nullptr)
            : base_type(priority, left, right), _value(value) {}

    const value_type *get_value_address() const { return std::addressof(_value); }

    value_type *get_value_address() { return std::addressof(_value); }

    key_type get_key() const { return base_type::left_size(); }

    value_type &get_value() { return _value; }

    const value_type &get_value() const { return _value; }

private:
    value_type _value;
};

template<typename T, typename Allocator>
class implicit_treap : public treap_base<implicit_treap_node<T>, Allocator> {
    using base_type = treap_base<implicit_treap_node<T>, Allocator>;
    using treap_node = implicit_treap_node<T>;
public:
    using typename base_type::key_type;
    using typename base_type::value_type;
    using typename base_type::allocator_type;
    using typename base_type::size_type;

private:
    using typename base_type::node_holder;

private:
    using base_type::_root;

public:
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

public:
    explicit implicit_treap(const allocator_type &allocator = allocator_type());

    implicit_treap(const implicit_treap &other);

    implicit_treap(implicit_treap &&other) noexcept;

    implicit_treap &operator=(const implicit_treap &other);

    implicit_treap &operator=(implicit_treap &&other) noexcept;

    ~implicit_treap() = default;

public:
    iterator push_back(const value_type &value);

    iterator push_back(value_type &&value);

    iterator insert(const value_type &value, size_type index);

    iterator insert(value_type &&value, size_type index);

    template<typename... Args>
    iterator emplace_back(Args &&... args);

    void erase(size_type index);

    value_type &operator[](size_type index);

    const value_type &operator[](size_type index) const;

public:
    using base_type::size;

    using base_type::empty;

private:
    template<typename... Args>
    iterator emplace(size_type index, Args &&... args);

private:
    treap_node *merge(treap_node *node1, treap_node *node2);

    std::pair<treap_node *, treap_node *> split(treap_node *node, size_type index);
};

template<typename Node, typename Allocator>
implicit_treap<Node, Allocator>::implicit_treap(const allocator_type &allocator)
        : base_type(allocator) {}

template<typename Node, typename Allocator>
implicit_treap<Node, Allocator>::implicit_treap(const implicit_treap &other)
        : base_type(other._node_allocator) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        emplace_back(*it);
    }
}

template<typename Node, typename Allocator>
implicit_treap<Node, Allocator>::implicit_treap(implicit_treap &&other) noexcept
        : base_type(std::move(other)) {}

template<typename Node, typename Allocator>
implicit_treap<Node, Allocator> &
implicit_treap<Node, Allocator>::operator=(const implicit_treap &other) {
    if (this != &other) {
        implicit_treap copied(other);
        this->swap(copied);
    }
    return *this;
}

template<typename Node, typename Allocator>
implicit_treap<Node, Allocator> &
implicit_treap<Node, Allocator>::operator=(implicit_treap &&other) noexcept {
    if (this != &other) {
        implicit_treap moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template<typename T, typename Allocator>
typename implicit_treap<T, Allocator>::treap_node *
implicit_treap<T, Allocator>::merge(treap_node *node1, treap_node *node2) {
    if (node1 == nullptr) {
        return node2;
    }
    if (node2 == nullptr) {
        return node1;
    }
    if (node1->get_priority() > node2->get_priority()) {
        node1->set_right(merge(node1->get_right(), node2));
        return node1;
    }
    node2->set_left(merge(node1, node2->get_left()));
    return node2;
}

template<typename T, typename Allocator>
auto implicit_treap<T, Allocator>::split(treap_node *node, size_type index) -> std::pair<treap_node *, treap_node *> {
    if (node == nullptr || index <= 0) {
        return std::make_pair(nullptr, node);
    }
    if (index >= node->size()) {
        return std::make_pair(node, nullptr);
    }
    if (node->left_size() < index) {
        auto right_pair = split(node->get_right(), index - node->left_size() - 1);
        node->set_right(right_pair.first);
        return {node, right_pair.second};
    }
    auto left_pair = split(node->get_left(), index);
    node->set_left(left_pair.second);
    return {left_pair.first, node};
}

template<typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::push_back(const value_type &value) {
    return emplace_back(value);
}

template<typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::push_back(value_type &&value) {
    return emplace_back(value);
}

template<typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator
implicit_treap<T, Allocator>::insert(const value_type &value, size_type index) {
    return emplace(index, value);
}

template<typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator
implicit_treap<T, Allocator>::insert(value_type &&value, size_type index) {
    return emplace(index, value);
}

template<typename T, typename Allocator>
template<typename ...Args>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::emplace_back(Args &&...args) {
    return emplace(size(), std::forward<Args>(args)...);
}

template<typename T, typename Allocator>
void implicit_treap<T, Allocator>::erase(size_type index) {
    auto first_split_pair = split(_root, index);
    auto second_split_pair = split(first_split_pair.second, 1);
    base_type::destroy_tree(second_split_pair.first);
    if (empty()) {
        _root = nullptr;
        return;
    }
    _root = merge(first_split_pair.first, second_split_pair.second);
}

template<typename T, typename Allocator>
typename implicit_treap<T, Allocator>::value_type &implicit_treap<T, Allocator>::operator[](size_type index) {
    return *(base_type::begin() + index);
}

template<typename T, typename Allocator>
const typename implicit_treap<T, Allocator>::value_type &
implicit_treap<T, Allocator>::operator[](size_type index) const {
    return *(base_type::cbegin() + index);
}

template<typename T, typename Allocator>
template<typename ...Args>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::emplace(size_type index, Args &&...args) {
    if (index > size()) {
        index = size();
    }
    // allocate memory for node and construct value
    node_holder holder = base_type::construct_node(std::forward<Args>(args)...);
    if (empty()) {
        _root = holder.release();
        return base_type::begin();
    }
    // insert new constructed node into tree
    std::pair<treap_node *, treap_node *> p = split(_root, index);
    _root = merge(merge(p.first, holder.get()), p.second);
    // release node holder, as insertion completed successfully
    auto *node = holder.release();
    return {node->get_value_address(), this, index};
}

#endif // BASICS_IMPLICIT_TREAP_BASE_H