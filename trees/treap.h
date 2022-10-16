#pragma once

#include <utility>
#include <memory>
#include "../iterators/reverse_iterator.h"

class TreapNode {
public:
    using value_type = int;

public:
    explicit TreapNode(value_type key = 0, unsigned int priority = 0, TreapNode *left = nullptr, TreapNode *right = nullptr)
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

class Treap {
public:
    int maxDepth() const;
    int maxDepth(const TreapNode* node) const;
private:
    TreapNode* _root;
public:
    typedef int value_type;
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

    const value_type& keyOfOrder(size_t index) const;

    size_t orderOfKey(const value_type& index) const;

    bool empty() const { return size() == 0; }

    size_t size() const { return _root != nullptr ? _root->size() : 0; }

private:
    void deallocate(TreapNode* node);

private:
    TreapNode* nodeOfKey(const value_type& value);

    const TreapNode* nodeOfKey(const value_type& value) const;

    TreapNode* nodeOfOrder(size_t index);

    const TreapNode* nodeOfOrder(size_t index) const;

    size_t orderOfKey(const value_type& value, const TreapNode* node) const;

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


template<bool B>
Treap::common_iterator<B>::common_iterator(value_type* value, treap_type& treap, size_t index)
        :_value(value), _treap(treap), _index(index) {}


template<bool B>
typename Treap::template common_iterator<B>& Treap::common_iterator<B>::operator++() {
    auto* node = _treap.nodeOfOrder(++_index);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<bool B>
typename Treap::template common_iterator<B> Treap::common_iterator<B>::operator++(int) {
    common_iterator iter = *this;
    ++(*this);
    return iter;
}


template<bool B>
typename Treap::template common_iterator<B> &Treap::common_iterator<B>::operator+=(ptrdiff_t n) {
    auto* node = _treap.nodeOfOrder(_index += n);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<bool B>
typename Treap::template common_iterator<B> &Treap::common_iterator<B>::operator--() {
    auto* node = _treap.nodeOfOrder(--_index);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<bool B>
typename Treap::template common_iterator<B> Treap::common_iterator<B>::operator--(int) {
    common_iterator iter = *this;
    --(*this);
    return iter;
}


template<bool B>
typename Treap::template common_iterator<B> &Treap::common_iterator<B>::operator-=(ptrdiff_t n) {
    auto* node = _treap.nodeOfOrder(_index -= n);
    _value = (node == nullptr ? nullptr : &node->key);
    return *this;
}


template<bool B>
ptrdiff_t Treap::common_iterator<B>::operator-(const common_iterator<B> &iter) const {
    return static_cast<ptrdiff_t>(_index) - iter._index;
}


template<bool B>
auto Treap::common_iterator<B>::operator*() -> value_type& {
    return *_value;
}


template<bool B>
auto Treap::common_iterator<B>::operator->() -> value_type* {
    return _value;
}


template<bool B>
bool Treap::common_iterator<B>::operator==(const common_iterator<B> &iter) const {
    return _value == iter._value;
}


template<bool B>
bool Treap::common_iterator<B>::operator!=(const common_iterator<B> &iter) const {
    return _value != iter._value;
}


template<bool B>
bool Treap::common_iterator<B>::operator<(const common_iterator<B> &iter) const {
    return _index < iter._index;
}


template<bool B>
bool Treap::common_iterator<B>::operator>(const common_iterator<B> &iter) const {
    return _index > iter._index;
}


template<bool B>
bool Treap::common_iterator<B>::operator<=(const common_iterator<B> &iter) const {
    return _index <= iter._index;
}


template<bool B>
bool Treap::common_iterator<B>::operator>=(const common_iterator<B> &iter) const {
    return _index >= iter._index;
}


template<bool B>
typename Treap::template common_iterator<B> Treap::common_iterator<B>::operator+(ptrdiff_t n) {
    common_iterator<B> iter = *this;
    return iter += n;
}


template<bool B>
typename Treap::template common_iterator<B> Treap::common_iterator<B>::operator-(ptrdiff_t n) {
    common_iterator<B> iter = *this;
    return iter -= n;
}