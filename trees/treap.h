#pragma once

#include <utility>
#include <memory>
#include <chrono>
#include <random>
#include "../iterators/reverse_iterator.h"

template<typename T>
class TreapNode {
public:
    using value_type = T;

public:
    explicit TreapNode(const value_type& key, unsigned int priority = 0, TreapNode *left = nullptr, TreapNode *right = nullptr)
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
    static TreapNode *merge(TreapNode* node1, TreapNode* node2);

    static std::pair<TreapNode *, TreapNode *> split(TreapNode* node, const value_type& value);

private:
    void update() { _size = leftSize() + rightSize() + 1; }

public:
    value_type key;
private:
    unsigned int _priority;
    TreapNode *_left;
    TreapNode *_right;
    size_t _size;
};

template<typename T>
class Treap {
public:
    int maxDepth() const;
    int maxDepth(const TreapNode<T>* node) const;
private:
    TreapNode<T>* _root;
public:
    using value_type = T;
public:
    Treap();

    Treap(const Treap &other);

    Treap(Treap &&other) noexcept;

    Treap &operator=(const Treap &other);

    Treap &operator=(Treap &&other) noexcept;

    ~Treap();

    void swap(Treap &other) noexcept;

    void insert(const value_type& value);

    void remove(const value_type& value);

    bool contains(const value_type& value) const;

    const typename TreapNode<T>::value_type& keyOfOrder(size_t index) const;

    size_t orderOfKey(const value_type& index) const;

    bool empty() const { return size() == 0; }

    size_t size() const { return _root != nullptr ? _root->size() : 0; }

private:
    void deallocate(TreapNode<T>* node);

private:
    TreapNode<T>* nodeOfKey(const value_type& value);

    const TreapNode<T>* nodeOfKey(const value_type& value) const;

    TreapNode<T>* nodeOfOrder(size_t index);

    const TreapNode<T>* nodeOfOrder(size_t index) const;

    size_t orderOfKey(const value_type& value, const TreapNode<T>* node) const;

private:
    template<bool B>
    class common_iterator {
    public:
        using value_type = std::conditional_t<B, const Treap::value_type, Treap::value_type>;
        using treap_type = std::conditional_t<B, const Treap, Treap>;
    private:
        value_type* _value;
        treap_type& _treap;
        size_t _index;
    public:
        common_iterator(value_type* value, treap_type& treap, size_t index);

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

private:


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


template<typename T>
template<bool B>
Treap<T>::common_iterator<B>::common_iterator(value_type* value, treap_type& treap, size_t index)
        :_value(value), _treap(treap), _index(index) {}

template<typename T>
template<bool B>
typename Treap<T>::template common_iterator<B>& Treap<T>::common_iterator<B>::operator++() {
    auto* node = _treap.nodeOfOrder(++_index);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<typename T>
template<bool B>
typename Treap<T>::template common_iterator<B> Treap<T>::common_iterator<B>::operator++(int) {
    common_iterator iter = *this;
    ++(*this);
    return iter;
}


template<typename T>
template<bool B>
typename Treap<T>::template common_iterator<B> &Treap<T>::common_iterator<B>::operator+=(ptrdiff_t n) {
    auto* node = _treap.nodeOfOrder(_index += n);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<typename T>
template<bool B>
typename Treap<T>::template common_iterator<B> &Treap<T>::common_iterator<B>::operator--() {
    auto* node = _treap.nodeOfOrder(--_index);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<typename T>
template<bool B>
typename Treap<T>::template common_iterator<B> Treap<T>::common_iterator<B>::operator--(int) {
    common_iterator iter = *this;
    --(*this);
    return iter;
}


template<typename T>
template<bool B>
typename Treap<T>::template common_iterator<B> &Treap<T>::common_iterator<B>::operator-=(ptrdiff_t n) {
    auto* node = _treap.nodeOfOrder(_index -= n);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<typename T>
template<bool B>
ptrdiff_t Treap<T>::common_iterator<B>::operator-(const common_iterator<B> &iter) const {
    return static_cast<ptrdiff_t>(_index) - iter._index;
}


template<typename T>
template<bool B>
auto Treap<T>::common_iterator<B>::operator*() -> value_type& {
    return *_value;
}


template<typename T>
template<bool B>
auto Treap<T>::common_iterator<B>::operator->() -> value_type* {
    return _value;
}


template<typename T>
template<bool B>
bool Treap<T>::common_iterator<B>::operator==(const common_iterator<B> &iter) const {
    return _value == iter._value;
}


template<typename T>
template<bool B>
bool Treap<T>::common_iterator<B>::operator!=(const common_iterator<B> &iter) const {
    return _value != iter._value;
}


template<typename T>
template<bool B>
bool Treap<T>::common_iterator<B>::operator<(const common_iterator<B> &iter) const {
    return _index < iter._index;
}


template<typename T>
template<bool B>
bool Treap<T>::common_iterator<B>::operator>(const common_iterator<B> &iter) const {
    return _index > iter._index;
}


template<typename T>
template<bool B>
bool Treap<T>::common_iterator<B>::operator<=(const common_iterator<B> &iter) const {
    return _index <= iter._index;
}


template<typename T>
template<bool B>
bool Treap<T>::common_iterator<B>::operator>=(const common_iterator<B> &iter) const {
    return _index >= iter._index;
}


template<typename T>
template<bool B>
typename Treap<T>::template common_iterator<B> Treap<T>::common_iterator<B>::operator+(ptrdiff_t n) {
    common_iterator<B> iter = *this;
    return iter += n;
}


template<typename T>
template<bool B>
typename Treap<T>::template common_iterator<B> Treap<T>::common_iterator<B>::operator-(ptrdiff_t n) {
    common_iterator<B> iter = *this;
    return iter -= n;
}


template<typename T>
TreapNode<T> *TreapNode<T>::copy() const {
    auto *root = new TreapNode(key, _priority);
    if (_left != nullptr) {
        root->setLeft(_left->copy());
    }
    if (_right != nullptr) {
        root->setRight(_right->copy());
    }
    return root;
}


template<typename T>
TreapNode<T> *TreapNode<T>::merge(TreapNode<T> *node1, TreapNode<T> *node2) {
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

template<typename T>
std::pair<TreapNode<T> *, TreapNode<T> *> TreapNode<T>::split(TreapNode<T> *node, const value_type &value) {
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

template<typename T>
Treap<T>::Treap()
        : _root(nullptr) {}

template<typename T>
Treap<T>::Treap(const Treap<T> &other)
        : _root(other._root->copy()) {}

template<typename T>
Treap<T>::Treap(Treap<T> &&other) noexcept
        : _root(std::exchange(other._root, nullptr)) {}

template<typename T>
Treap<T> &Treap<T>::operator=(const Treap<T> &other) {
    if (this != &other) {
        Treap<T> copied(other);
        swap(copied);
    }
    return *this;
}

template<typename T>
Treap<T> &Treap<T>::operator=(Treap<T> &&other) noexcept {
    if (this != &other) {
        Treap<T> moved(std::move(other));
        swap(moved);
    }
    return *this;
}

template<typename T>
Treap<T>::~Treap() {
    deallocate(_root);
}

template<typename T>
void Treap<T>::swap(Treap<T> &other) noexcept {
    std::swap(_root, other._root);
}

template<typename T>
void Treap<T>::insert(const value_type &value) {
    if (contains(value)) {
        return;
    }
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    auto *my_node = new TreapNode<T>(value, rng());
    if (_root == nullptr) {
        _root = my_node;
        return;
    }
    std::pair<TreapNode<T> *, TreapNode<T> *> p = TreapNode<T>::split(_root, value);
    _root = TreapNode<T>::merge(p.second, TreapNode<T>::merge(p.first, my_node));
}

template<typename T>
void Treap<T>::remove(const value_type &value) {
    std::pair<TreapNode<T> *, TreapNode<T> *> first_split_pair = TreapNode<T>::split(_root, value);
    std::pair<TreapNode<T> *, TreapNode<T> *> second_split_pair = TreapNode<T>::split(first_split_pair.second, value + 1);
    if (second_split_pair.first == nullptr) {
        throw std::runtime_error("Element not found");
    }
    delete second_split_pair.first;
    if (empty()) {
        _root = nullptr;
        return;
    }
    _root = TreapNode<T>::merge(first_split_pair.first, second_split_pair.second);
}

template<typename T>
bool Treap<T>::contains(const value_type &value) const {
    return nodeOfKey(value) != nullptr;
}

template<typename T>
TreapNode<T> *Treap<T>::nodeOfKey(const value_type &value) {
    return const_cast<TreapNode<T> *>(const_cast<const Treap<T> *>(this)->nodeOfKey(value));
}

template<typename T>
const TreapNode<T> *Treap<T>::nodeOfKey(const value_type &value) const {
    TreapNode<T> *root = _root;
    while (root != nullptr && value != root->key) {
        if (value < root->key) {
            root = root->getLeft();
            continue;
        }
        root = root->getRight();
    }
    return root;
}

template<typename T>
TreapNode<T> *Treap<T>::nodeOfOrder(size_t index) {
    return const_cast<TreapNode<T> *>(const_cast<const Treap<T> *>(this)->nodeOfOrder(index));
}

template<typename T>
const TreapNode<T> *Treap<T>::nodeOfOrder(size_t index) const {
    if (index == size()) {
        return nullptr;
    }
    if (index > size()) {
        throw std::out_of_range("Index out of bounds");
    }
    ++index;
    TreapNode<T> *root = _root;
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

template<typename T>
const typename TreapNode<T>::value_type &Treap<T>::keyOfOrder(size_t index) const {
    return nodeOfOrder(index)->key;
}

template<typename T>
size_t Treap<T>::orderOfKey(const value_type &key) const {
    return orderOfKey(key, _root) - 1;
}

template<typename T>
size_t Treap<T>::orderOfKey(const value_type &key, const TreapNode<T> *root) const {
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

template<typename T>
void Treap<T>::deallocate(TreapNode<T> *node) {
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


template<typename T>
int Treap<T>::maxDepth() const {
    return maxDepth(_root);
}

template<typename T>
int Treap<T>::maxDepth(const TreapNode<T> *node) const {
    if (node == nullptr) {
        return 0;
    }
    return std::max(maxDepth(node->getRight()), maxDepth(node->getLeft())) + 1;
}

template<typename T>
typename Treap<T>::iterator Treap<T>::begin() const {
    return cbegin();
}

template<typename T>
typename Treap<T>::iterator Treap<T>::end() const {
    return cend();
}

template<typename T>
typename Treap<T>::reverse_iterator Treap<T>::rbegin() const {
    return {end()};
}

template<typename T>
typename Treap<T>::reverse_iterator Treap<T>::rend() const {
    return {begin()};
}

template<typename T>
typename Treap<T>::const_iterator Treap<T>::cbegin() const {
    if (empty()) {
        return cend();
    }
    const size_t index = 0;
    return {&nodeOfOrder(index)->key, *this, index};
}

template<typename T>
typename Treap<T>::const_iterator Treap<T>::cend() const {
    return {nullptr, *this, size()};
}

template<typename T>
typename Treap<T>::const_reverse_iterator Treap<T>::crbegin() const {
    return {cend()};
}

template<typename T>
typename Treap<T>::const_reverse_iterator Treap<T>::crend() const {
    return {cbegin()};
}