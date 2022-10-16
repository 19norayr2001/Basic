#pragma once

#include <utility>
#include <memory>
#include <chrono>
#include <random>
#include "../iterators/reverse_iterator.h"

template<typename Key, typename Compare = std::less<Key>>
class Treap {
public:
    using key_type = Key;
    using key_compare = Compare;
private:
    class TreapNode {
    public:
        explicit TreapNode(const key_type &key, unsigned int priority = 0, TreapNode *left = nullptr,
                           TreapNode *right = nullptr)
                : key(key), _priority(priority), _left(left), _right(right), _size(1) { update(); }

    public:
        void setLeft(TreapNode *node) {
            _left = node;
            update();
        }

        void setRight(TreapNode *node) {
            _right = node;
            update();
        }

        TreapNode *getLeft() { return _left; }

        const TreapNode *getLeft() const { return _left; }

        TreapNode *getRight() { return _right; }

        const TreapNode *getRight() const { return _right; }

        size_t size() const { return _size; }

        size_t leftSize() const { return (_left != nullptr ? _left->_size : 0); }

        size_t rightSize() const { return (_right != nullptr ? _right->_size : 0); }

    public:
        TreapNode *copy() const;

    public:
        static TreapNode *merge(TreapNode *node1, TreapNode *node2);

        static std::pair<TreapNode *, TreapNode *> split(TreapNode *node, const key_type &value);

    private:
        void update() { _size = leftSize() + rightSize() + 1; }

    public:
        key_type key;
    private:
        unsigned int _priority;
        TreapNode *_left;
        TreapNode *_right;
        size_t _size;
    };

private:
    TreapNode *_root;
    key_compare _comparator;

public:
    int maxDepth() const;

    int maxDepth(const TreapNode *node) const;

public:
    Treap(const key_compare& comparator = key_compare());

    Treap(const Treap &other);

    Treap(Treap &&other) noexcept;

    Treap &operator=(const Treap &other);

    Treap &operator=(Treap &&other) noexcept;

    ~Treap();

    void swap(Treap &other) noexcept;

    void insert(const key_type &value);

    void remove(const key_type &value);

    bool contains(const key_type &value) const;

    const key_type &keyOfOrder(size_t index) const;

    size_t orderOfKey(const key_type &index) const;

    bool empty() const { return size() == 0; }

    size_t size() const { return _root != nullptr ? _root->size() : 0; }

private:
    void deallocate(TreapNode *node);

private:
    TreapNode *nodeOfKey(const key_type &value);

    const TreapNode *nodeOfKey(const key_type &value) const;

    TreapNode *nodeOfOrder(size_t index);

    const TreapNode *nodeOfOrder(size_t index) const;

    size_t orderOfKey(const key_type &value, const TreapNode *node) const;

private:
    template<bool B>
    class common_iterator {
    public:
        using value_type = std::conditional_t<B, const Treap::key_type, Treap::key_type>;
        using treap_type = std::conditional_t<B, const Treap, Treap>;
    private:
        value_type *_value;
        treap_type &_treap;
        size_t _index;
    public:
        common_iterator(value_type *value, treap_type &treap, size_t index);

    public:
        common_iterator<B> &operator++();

        common_iterator<B> operator++(int);

        common_iterator<B> &operator+=(ptrdiff_t);

        common_iterator<B> &operator--();

        common_iterator<B> operator--(int);

        common_iterator<B> &operator-=(ptrdiff_t);

    public:
        ptrdiff_t operator-(const common_iterator<B> &) const;

    public:
        value_type &operator*();

        value_type *operator->();

    public:
        bool operator==(const common_iterator<B> &) const;

        bool operator!=(const common_iterator<B> &) const;

        bool operator<(const common_iterator<B> &) const;

        bool operator>(const common_iterator<B> &) const;

        bool operator<=(const common_iterator<B> &) const;

        bool operator>=(const common_iterator<B> &) const;

    public:
        common_iterator<B> operator+(ptrdiff_t);

        common_iterator<B> operator-(ptrdiff_t);
    };

public:
    using iterator = common_iterator<true>;
    using const_iterator = common_iterator<true>;
    using reverse_iterator = common_reverse_iterator<iterator>;
    using const_reverse_iterator = common_reverse_iterator<const_iterator>;
public:
    iterator begin() const;

    iterator end() const;

    reverse_iterator rbegin() const;

    reverse_iterator rend() const;

    const_iterator cbegin() const;

    const_iterator cend() const;

    const_reverse_iterator crbegin() const;

    const_reverse_iterator crend() const;
};

//======================common_iterator implementation==========================================


template<typename Key, typename Compare>
template<bool B>
Treap<Key, Compare>::common_iterator<B>::common_iterator(value_type *value, treap_type &treap, size_t index)
        :_value(value), _treap(treap), _index(index) {}

template<typename Key, typename Compare>
template<bool B>
typename Treap<Key, Compare>::template common_iterator<B> &Treap<Key, Compare>::common_iterator<B>::operator++() {
    auto *node = _treap.nodeOfOrder(++_index);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<typename Key, typename Compare>
template<bool B>
typename Treap<Key, Compare>::template common_iterator<B> Treap<Key, Compare>::common_iterator<B>::operator++(int) {
    common_iterator iter = *this;
    ++(*this);
    return iter;
}


template<typename Key, typename Compare>
template<bool B>
typename Treap<Key, Compare>::template common_iterator<B> &
Treap<Key, Compare>::common_iterator<B>::operator+=(ptrdiff_t n) {
    auto *node = _treap.nodeOfOrder(_index += n);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<typename Key, typename Compare>
template<bool B>
typename Treap<Key, Compare>::template common_iterator<B> &Treap<Key, Compare>::common_iterator<B>::operator--() {
    auto *node = _treap.nodeOfOrder(--_index);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<typename Key, typename Compare>
template<bool B>
typename Treap<Key, Compare>::template common_iterator<B> Treap<Key, Compare>::common_iterator<B>::operator--(int) {
    common_iterator iter = *this;
    --(*this);
    return iter;
}


template<typename Key, typename Compare>
template<bool B>
typename Treap<Key, Compare>::template common_iterator<B> &
Treap<Key, Compare>::common_iterator<B>::operator-=(ptrdiff_t n) {
    auto *node = _treap.nodeOfOrder(_index -= n);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<typename Key, typename Compare>
template<bool B>
ptrdiff_t Treap<Key, Compare>::common_iterator<B>::operator-(const common_iterator<B> &iter) const {
    return static_cast<ptrdiff_t>(_index) - iter._index;
}


template<typename Key, typename Compare>
template<bool B>
auto Treap<Key, Compare>::common_iterator<B>::operator*() -> value_type & {
    return *_value;
}


template<typename Key, typename Compare>
template<bool B>
auto Treap<Key, Compare>::common_iterator<B>::operator->() -> value_type * {
    return _value;
}


template<typename Key, typename Compare>
template<bool B>
bool Treap<Key, Compare>::common_iterator<B>::operator==(const common_iterator<B> &iter) const {
    return _value == iter._value;
}


template<typename Key, typename Compare>
template<bool B>
bool Treap<Key, Compare>::common_iterator<B>::operator!=(const common_iterator<B> &iter) const {
    return _value != iter._value;
}


template<typename Key, typename Compare>
template<bool B>
bool Treap<Key, Compare>::common_iterator<B>::operator<(const common_iterator<B> &iter) const {
    return _index < iter._index;
}


template<typename Key, typename Compare>
template<bool B>
bool Treap<Key, Compare>::common_iterator<B>::operator>(const common_iterator<B> &iter) const {
    return _index > iter._index;
}


template<typename Key, typename Compare>
template<bool B>
bool Treap<Key, Compare>::common_iterator<B>::operator<=(const common_iterator<B> &iter) const {
    return _index <= iter._index;
}


template<typename Key, typename Compare>
template<bool B>
bool Treap<Key, Compare>::common_iterator<B>::operator>=(const common_iterator<B> &iter) const {
    return _index >= iter._index;
}


template<typename Key, typename Compare>
template<bool B>
typename Treap<Key, Compare>::template common_iterator<B>
Treap<Key, Compare>::common_iterator<B>::operator+(ptrdiff_t n) {
    common_iterator<B> iter = *this;
    return iter += n;
}


template<typename Key, typename Compare>
template<bool B>
typename Treap<Key, Compare>::template common_iterator<B>
Treap<Key, Compare>::common_iterator<B>::operator-(ptrdiff_t n) {
    common_iterator<B> iter = *this;
    return iter -= n;
}


template<typename Key, typename Compare>
typename Treap<Key, Compare>::TreapNode *Treap<Key, Compare>::TreapNode::copy() const {
    auto *root = new TreapNode(key, _priority);
    if (_left != nullptr) {
        root->setLeft(_left->copy());
    }
    if (_right != nullptr) {
        root->setRight(_right->copy());
    }
    return root;
}


template<typename Key, typename Compare>
typename Treap<Key, Compare>::TreapNode *Treap<Key, Compare>::TreapNode::merge(TreapNode *node1, TreapNode *node2) {
    if (node1 == nullptr) {
        return node2;
    }
    if (node2 == nullptr) {
        return node1;
    }
    if (node1->key > node2->key) {
        std::swap(node1, node2);
    }
    if (node1->_priority > node2->_priority) {
        node1->setRight(merge(node1->getRight(), node2));
        return node1;
    }
    node2->setLeft(merge(node1, node2->getLeft()));
    return node2;
}

template<typename Key, typename Compare>
std::pair<typename Treap<Key, Compare>::TreapNode *, typename Treap<Key, Compare>::TreapNode *>
Treap<Key, Compare>::TreapNode::split(TreapNode *node, const key_type &value) {
    if (node == nullptr) {
        return std::make_pair(nullptr, nullptr);
    }
    if (node->key < value) {
        std::pair<TreapNode *, TreapNode *> pair_right = TreapNode::split(node->getRight(), value);
        node->setRight(pair_right.first);
        return {node, pair_right.second};
    }
    std::pair<TreapNode *, TreapNode *> pair_left = TreapNode::split(node->getLeft(), value);
    node->setLeft(pair_left.second);
    return {pair_left.first, node};
}

template<typename Key, typename Compare>
Treap<Key, Compare>::Treap(const key_compare& comparator)
        : _root(nullptr), _comparator(comparator) {}

template<typename Key, typename Compare>
Treap<Key, Compare>::Treap(const Treap<Key, Compare> &other)
        : _root(other._root->copy()), _comparator(other._comparator) {}

template<typename Key, typename Compare>
Treap<Key, Compare>::Treap(Treap<Key, Compare> &&other) noexcept
        : _root(std::exchange(other._root, nullptr)), _comparator(std::move(other._comparator)) {}

template<typename Key, typename Compare>
Treap<Key, Compare> &Treap<Key, Compare>::operator=(const Treap<Key, Compare> &other) {
    if (this != &other) {
        Treap<Key, Compare> copied(other);
        swap(copied);
    }
    return *this;
}

template<typename Key, typename Compare>
Treap<Key, Compare> &Treap<Key, Compare>::operator=(Treap<Key, Compare> &&other) noexcept {
    if (this != &other) {
        Treap<Key, Compare> moved(std::move(other));
        swap(moved);
    }
    return *this;
}

template<typename Key, typename Compare>
Treap<Key, Compare>::~Treap() {
    deallocate(_root);
}

template<typename Key, typename Compare>
void Treap<Key, Compare>::swap(Treap<Key, Compare> &other) noexcept {
    std::swap(_root, other._root);
}

template<typename Key, typename Compare>
void Treap<Key, Compare>::insert(const key_type &value) {
    if (contains(value)) {
        return;
    }
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    auto *my_node = new TreapNode(value, rng());
    if (_root == nullptr) {
        _root = my_node;
        return;
    }
    std::pair<TreapNode *, TreapNode *> p = TreapNode::split(_root, value);
    _root = TreapNode::merge(p.second, TreapNode::merge(p.first, my_node));
}

template<typename Key, typename Compare>
void Treap<Key, Compare>::remove(const key_type &value) {
    std::pair<TreapNode *, TreapNode *> first_split_pair = TreapNode::split(_root, value);
    std::pair<TreapNode *, TreapNode *> second_split_pair = TreapNode::split(first_split_pair.second,
                                                                             value + 1);
    if (second_split_pair.first == nullptr) {
        throw std::runtime_error("Element not found");
    }
    delete second_split_pair.first;
    if (empty()) {
        _root = nullptr;
        return;
    }
    _root = TreapNode::merge(first_split_pair.first, second_split_pair.second);
}

template<typename Key, typename Compare>
bool Treap<Key, Compare>::contains(const key_type &value) const {
    return nodeOfKey(value) != nullptr;
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::TreapNode *Treap<Key, Compare>::nodeOfKey(const key_type &value) {
    return const_cast<TreapNode *>(const_cast<const Treap<Key, Compare> *>(this)->nodeOfKey(value));
}

template<typename Key, typename Compare>
const typename Treap<Key, Compare>::TreapNode *Treap<Key, Compare>::nodeOfKey(const key_type &value) const {
    TreapNode *root = _root;
    while (root != nullptr && value != root->key) {
        if (value < root->key) {
            root = root->getLeft();
            continue;
        }
        root = root->getRight();
    }
    return root;
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::TreapNode *Treap<Key, Compare>::nodeOfOrder(size_t index) {
    return const_cast<TreapNode *>(const_cast<const Treap<Key, Compare> *>(this)->nodeOfOrder(index));
}

template<typename Key, typename Compare>
const typename Treap<Key, Compare>::TreapNode *Treap<Key, Compare>::nodeOfOrder(size_t index) const {
    if (index == size()) {
        return nullptr;
    }
    if (index > size()) {
        throw std::out_of_range("Index out of bounds");
    }
    ++index;
    TreapNode *root = _root;
    while (root != nullptr) {
        size_t left_count = root->leftSize();
        if (index == left_count + 1) {
            return root;
        }
        if (index <= left_count) {
            root = root->getLeft();
            continue;
        }
        root = root->getRight();
        index -= left_count + 1;
    }
    throw std::runtime_error("Unreachable code");
}

template<typename Key, typename Compare>
const typename Treap<Key, Compare>::key_type &Treap<Key, Compare>::keyOfOrder(size_t index) const {
    return nodeOfOrder(index)->key;
}

template<typename Key, typename Compare>
size_t Treap<Key, Compare>::orderOfKey(const key_type &key) const {
    return orderOfKey(key, _root) - 1;
}

template<typename Key, typename Compare>
size_t Treap<Key, Compare>::orderOfKey(const key_type &key, const TreapNode *root) const {
    if (root == nullptr) {
        throw std::runtime_error("Element not found");
    }
    if (key == root->key) {
        return 1 + root->leftSize();
    }
    if (key < root->key) {
        return orderOfKey(key, root->getLeft());
    }
    return 1 + root->leftSize() + orderOfKey(key, root->getRight());
}

template<typename Key, typename Compare>
void Treap<Key, Compare>::deallocate(TreapNode *node) {
    if (node == nullptr) {
        return;
    }
    if (node->getLeft() != nullptr) {
        deallocate(node->getLeft());
    }
    if (node->getRight() != nullptr) {
        deallocate(node->getRight());
    }
    delete node;
}


template<typename Key, typename Compare>
int Treap<Key, Compare>::maxDepth() const {
    return maxDepth(_root);
}

template<typename Key, typename Compare>
int Treap<Key, Compare>::maxDepth(const TreapNode *node) const {
    if (node == nullptr) {
        return 0;
    }
    return std::max(maxDepth(node->getRight()), maxDepth(node->getLeft())) + 1;
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::iterator Treap<Key, Compare>::begin() const {
    return cbegin();
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::iterator Treap<Key, Compare>::end() const {
    return cend();
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::reverse_iterator Treap<Key, Compare>::rbegin() const {
    return {end()};
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::reverse_iterator Treap<Key, Compare>::rend() const {
    return {begin()};
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::const_iterator Treap<Key, Compare>::cbegin() const {
    if (empty()) {
        return cend();
    }
    const size_t index = 0;
    return {&nodeOfOrder(index)->key, *this, index};
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::const_iterator Treap<Key, Compare>::cend() const {
    return {nullptr, *this, size()};
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::const_reverse_iterator Treap<Key, Compare>::crbegin() const {
    return {cend()};
}

template<typename Key, typename Compare>
typename Treap<Key, Compare>::const_reverse_iterator Treap<Key, Compare>::crend() const {
    return {cbegin()};
}