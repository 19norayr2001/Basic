#ifndef BASICS_TREAP_H
#define BASICS_TREAP_H

#include <utility>
#include <memory>
#include <chrono>
#include <random>
#include <stack>
#include <treap_base.h>

template<typename Node, typename Compare, typename Allocator>
class treap : public treap_base<Node, Allocator> {
    using _base = treap_base<Node, Allocator>;
public:
    using key_type = typename _base::key_type;
    using value_type = typename _base::value_type;
    using key_compare = Compare;
    using allocator_type = typename _base::allocator_type;
    using size_type = typename _base::size_type;

private:
    using treap_node = Node;
    using node_holder = typename _base::node_holder;

public:
    using iterator = typename _base::iterator;
    using const_iterator = typename _base::const_iterator;
    using reverse_iterator = typename _base::reverse_iterator;
    using const_reverse_iterator = typename _base::const_reverse_iterator;

private:
    using _base::_root;

    key_compare _comparator;

public:
    explicit treap(const key_compare &comparator = key_compare(), const allocator_type &allocator = allocator_type());

    treap(const treap &other);

    treap(treap &&other) noexcept;

    treap &operator=(const treap &other);

    treap &operator=(treap &&other) noexcept;

    ~treap() = default;

private:

    treap_node *merge(treap_node *node1, treap_node *node2);

    template<bool KeyIncluded = false>
    std::pair<treap_node *, treap_node *> split(treap_node *node, const key_type &key);

public:
    void swap(treap &other) noexcept;

    std::pair<iterator, bool> insert(const key_type &key);

    std::pair<iterator, bool> insert(key_type &&key);

    template<typename... Args>
    std::pair<iterator, bool> emplace(Args &&... args);

    void erase(const key_type &key);

    bool contains(const key_type &key) const;

    iterator find(const key_type &key);

    const_iterator find(const key_type &key) const;

    const key_type &key_of_order(size_type index) const;

    size_type order_of_key(const key_type &key) const;

    using _base::size;

    using _base::empty;

private:
    iterator iterator_of_key(const key_type &key);

    const_iterator iterator_of_key(const key_type &key) const;

public:
    using _base::begin;

    using _base::cbegin;

    using _base::rbegin;

    using _base::crbegin;

    using _base::end;

    using _base::cend;

    using _base::rend;

    using _base::crend;

private:
    iterator const_cast_iterator(const const_iterator &it);
};

template<typename Node, typename Compare, typename Allocator>
treap<Node, Compare, Allocator>::treap(const key_compare &comparator, const allocator_type &allocator)
        : _base(allocator), _comparator(comparator) {}

template<typename Node, typename Compare, typename Allocator>
treap<Node, Compare, Allocator>::treap(const treap &other)
        : _base(other._node_allocator), _comparator(other._comparator) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        insert(*it);
    }
}

template<typename Node, typename Compare, typename Allocator>
treap<Node, Compare, Allocator>::treap(treap &&other) noexcept
        : _base(std::move(other)), _comparator(std::move(other._comparator)) {}

template<typename Node, typename Compare, typename Allocator>
treap<Node, Compare, Allocator> &
treap<Node, Compare, Allocator>::operator=(const treap &other) {
    if (this != &other) {
        treap<Node, Compare, Allocator> copied(other);
        this->swap(copied);
    }
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
treap<Node, Compare, Allocator> &
treap<Node, Compare, Allocator>::operator=(treap &&other) noexcept {
    if (this != &other) {
        treap<Node, Compare, Allocator> moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
typename treap<Node, Compare, Allocator>::treap_node *
treap<Node, Compare, Allocator>::merge(treap_node *node1, treap_node *node2) {
    if (node1 == nullptr) {
        return node2;
    }
    if (node2 == nullptr) {
        return node1;
    }
    if (_comparator(node2->get_key(), node1->get_key())) {
        std::swap(node1, node2);
    }
    if (node1->get_priority() > node2->get_priority()) {
        node1->set_right(merge(node1->get_right(), node2));
        return node1;
    }
    node2->set_left(merge(node1, node2->get_left()));
    return node2;
}

template<typename Node, typename Compare, typename Allocator>
template<bool KeyIncluded>
auto
treap<Node, Compare, Allocator>::split(treap_node *node, const key_type &key) -> std::pair<treap_node *, treap_node *> {
    std::stack<treap_node *> nodes;
    std::stack<bool> compares;
    // gather all splittable nodes in stack
    nodes.push(node);
    while (nodes.top() != nullptr) {
        auto *top = nodes.top();
        bool compare = (KeyIncluded ? !_comparator(key, top->get_key()) : _comparator(top->get_key(), key));
        nodes.push(compare ? top->get_right() : top->get_left());
        // store comparison results in separate stack
        compares.push(compare);
    }
    // here we need two null pointers at the top of the stack
    nodes.push(nullptr);
    // in this point nodes count is greater comparison count by 2
    // so when the compares stack is empty, in nodes stack will be left two nodes, which are split results
    while (!compares.empty()) {
        bool compare = compares.top();
        auto *second = nodes.top();
        compares.pop(), nodes.pop();
        auto *first = nodes.top();
        nodes.pop();
        if (compare) {
            nodes.top()->set_right(first);
            nodes.push(second);
            continue;
        }
        nodes.top()->set_left(second);
        std::swap(nodes.top(), first);
        nodes.push(first);
    }
    // return last two nodes in nodes stack
    auto *second = nodes.top();
    nodes.pop();
    auto *first = nodes.top();
    return {first, second};
}

template<typename Node, typename Compare, typename Allocator>
void treap<Node, Compare, Allocator>::swap(treap<Node, Compare, Allocator> &other) noexcept {
    _base::swap(other);
    std::swap(_comparator, other._comparator);
}

template<typename Node, typename Compare, typename Allocator>
std::pair<typename treap<Node, Compare, Allocator>::iterator, bool>
treap<Node, Compare, Allocator>::insert(const key_type &key) {
    return emplace(key);
}

template<typename Node, typename Compare, typename Allocator>
std::pair<typename treap<Node, Compare, Allocator>::iterator, bool>
treap<Node, Compare, Allocator>::insert(key_type &&key) {
    return emplace(std::move(key));
}

template<typename Node, typename Compare, typename Allocator>
template<typename... Args>
std::pair<typename treap<Node, Compare, Allocator>::iterator, bool>
treap<Node, Compare, Allocator>::emplace(Args &&... args) {
    // allocate memory for node and construct value
    node_holder holder = _base::construct_node(std::forward<Args>(args)...);
    // if the tree already contains key, then just return
    auto it = find(holder->get_key());
    if (it != end()) {
        // node holder will automatically deallocate memory and destroy value
        return {it, false};
    }
    if (_root == nullptr) {
        _root = holder.release();
        return {begin(), true};
    }
    // insert new constructed node into tree
    std::pair<treap_node *, treap_node *> p = split(_root, holder->get_key());
    _root = merge(p.second, merge(p.first, holder.get()));
    // release node holder, as insertion completed successfully
    auto *node = holder.release();
    size_type index = order_of_key(node->get_key());
    return {iterator(node->get_value_address(), this, index), true};
}

template<typename Node, typename Compare, typename Allocator>
void treap<Node, Compare, Allocator>::erase(const key_type &key) {
    std::pair<treap_node *, treap_node *> first_split_pair = split(_root, key);
    std::pair<treap_node *, treap_node *> second_split_pair = split<true>(first_split_pair.second, key);
    _base::destroy_tree(second_split_pair.first);
    if (empty()) {
        _root = nullptr;
        return;
    }
    _root = merge(first_split_pair.first, second_split_pair.second);
}

template<typename Node, typename Compare, typename Allocator>
bool treap<Node, Compare, Allocator>::contains(const key_type &key) const {
    return iterator_of_key(key) != end();
}

template<typename Node, typename Compare, typename Allocator>
typename treap<Node, Compare, Allocator>::iterator
treap<Node, Compare, Allocator>::find(const key_type &key) {
    return iterator_of_key(key);
}

template<typename Node, typename Compare, typename Allocator>
typename treap<Node, Compare, Allocator>::const_iterator
treap<Node, Compare, Allocator>::find(const key_type &key) const {
    return iterator_of_key(key);
}

template<typename Node, typename Compare, typename Allocator>
typename treap<Node, Compare, Allocator>::iterator
treap<Node, Compare, Allocator>::iterator_of_key(const key_type &key) {
    return const_cast_iterator(const_cast<const treap *>(this)->iterator_of_key(key));
}

template<typename Node, typename Compare, typename Allocator>
typename treap<Node, Compare, Allocator>::const_iterator
treap<Node, Compare, Allocator>::iterator_of_key(const key_type &key) const {
    const treap_node *root = _root;
    size_type pos = 0;
    while (root != nullptr) {
        if (_comparator(key, root->get_key())) {
            root = root->get_left();
            continue;
        }
        if (_comparator(root->get_key(), key)) {
            pos += 1 + root->left_size();
            root = root->get_right();
            continue;
        }
        return {root->get_value_address(), this, pos + root->left_size()};
    }
    return end();
}

template<typename Node, typename Compare, typename Allocator>
typename treap<Node, Compare, Allocator>::iterator
treap<Node, Compare, Allocator>::const_cast_iterator(const const_iterator &it) {
    size_type index = it - const_iterator(nullptr, this, 0);
    const value_type &const_value = *it;
    auto *value = const_cast<value_type *>(std::addressof(const_value));
    return {value, this, index};
}

template<typename Node, typename Compare, typename Allocator>
const typename treap<Node, Compare, Allocator>::key_type &
treap<Node, Compare, Allocator>::key_of_order(size_type index) const {
    return _base::node_of_order(index)->get_key();
}

template<typename Node, typename Compare, typename Allocator>
typename treap<Node, Compare, Allocator>::size_type
treap<Node, Compare, Allocator>::order_of_key(const key_type &key) const {
    auto it = iterator_of_key(key);
    // create dummy iterator in order to avoid additional calculations and improve performance
    auto dummy_iterator = const_iterator(nullptr, this, 0);
    return it - dummy_iterator;
}

#endif // BASICS_TREAP_H
