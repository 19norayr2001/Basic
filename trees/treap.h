#pragma once

#include <utility>
#include <memory>
#include <chrono>
#include <random>
#include <stack>
#include <reverse_iterator.h>

template<typename Node>
class treap_node_base {
    using treap_node = Node;
protected:
    using size_type = size_t;
    using priority_type = unsigned long long;
public:
    explicit treap_node_base(priority_type priority = 0, treap_node *left = nullptr,
                             treap_node *right = nullptr)
            : _priority(priority), _left(left), _right(right), _size(1) { update(); }

public:
    void set_members(priority_type priority = 0, treap_node *left = nullptr, treap_node *right = nullptr) {
        _priority = priority;
        _left = left;
        _right = right;
        update();
    }

public:
    void set_left(treap_node *node) {
        _left = node;
        update();
    }

    void set_right(treap_node *node) {
        _right = node;
        update();
    }

    treap_node *get_left() { return _left; }

    const treap_node *get_left() const { return _left; }

    treap_node *get_right() { return _right; }

    const treap_node *get_right() const { return _right; }

    size_type size() const { return _size; }

    size_type left_size() const { return (_left != nullptr ? _left->_size : 0); }

    size_type right_size() const { return (_right != nullptr ? _right->_size : 0); }

    priority_type get_priority() const { return _priority; }

private:
    void update() { _size = left_size() + right_size() + 1; }

private:
    priority_type _priority;
    treap_node *_left;
    treap_node *_right;
    size_type _size;
};

template<typename Allocator>
class treap_node_destructor {
    using allocator_type = Allocator;
    using allocator_traits = std::allocator_traits<Allocator>;
public:
    using pointer = typename allocator_traits::pointer;
private:
    allocator_type &_allocator;
public:
    bool value_constructed;
public:
    treap_node_destructor(const treap_node_destructor &) = default;

    treap_node_destructor &operator=(const treap_node_destructor &) = delete;

    explicit treap_node_destructor(allocator_type &allocator, bool value_constructed = false) noexcept
            : _allocator(allocator), value_constructed(value_constructed) {}

    void operator()(pointer node) _NOEXCEPT {
        if (value_constructed) {
            allocator_traits::destroy(_allocator, node->get_value_address());
        }
        if (node) {
            allocator_traits::deallocate(_allocator, node, 1);
        }
    }
};

template<typename Node, typename Compare, typename Allocator>
class Treap {
public:
    using key_type = typename Node::key_type;
    using value_type = typename Node::value_type;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using size_type = size_t;
private:
    using treap_node = Node;
    using alloc_traits = std::allocator_traits<allocator_type>;
    using node_allocator_type = typename alloc_traits::template rebind_alloc<treap_node>;
    using node_traits = std::allocator_traits<node_allocator_type>;

private:
    using node_destructor = treap_node_destructor<node_allocator_type>;
    using node_holder = std::unique_ptr<treap_node, node_destructor>;

private:
    template<bool B>
    class common_iterator {
        friend class common_iterator<!B>;
    public:
        using value_type = std::conditional_t<B, const Treap::value_type, Treap::value_type>;
        using treap_type = std::conditional_t<B, const Treap, Treap>;
    private:
        value_type *_value;
        treap_type *_treap;
        size_type _index;
    public:
        common_iterator(value_type *value, treap_type *treap, size_type index);

        common_iterator(const common_iterator<false>& other);

        common_iterator& operator=(const common_iterator<false>& other);

    public:
        common_iterator<B> &operator++();

        common_iterator<B> operator++(int) &;

        common_iterator<B> &operator+=(ptrdiff_t);

        common_iterator<B> &operator--();

        common_iterator<B> operator--(int) &;

        common_iterator<B> &operator-=(ptrdiff_t);

    public:
        ptrdiff_t operator-(const common_iterator<B> &) const;

    public:
        value_type &operator*() const;

        value_type *operator->() const;

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
    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;
    using reverse_iterator = common_reverse_iterator<iterator>;
    using const_reverse_iterator = common_reverse_iterator<const_iterator>;

private:
    treap_node *_root;
    key_compare _comparator;
    node_allocator_type _node_allocator;
public:
    int maxDepth() const;

    int maxDepth(const treap_node *node) const;

public:
    explicit Treap(const key_compare &comparator = key_compare(), const allocator_type &allocator = allocator_type());

    Treap(std::initializer_list<value_type> il, const key_compare &comparator = key_compare(),
          const allocator_type &allocator = allocator_type());

    Treap(const Treap &other);

    Treap(Treap &&other) noexcept;

    Treap &operator=(const Treap &other);

    Treap &operator=(Treap &&other) noexcept;

    ~Treap();

private:
    void destroy_tree(treap_node *node);

    treap_node *merge(treap_node *node1, treap_node *node2);

    template<bool KeyIncluded = false>
    std::pair<treap_node *, treap_node *> split(treap_node *node, const key_type &key);

public:
    void swap(Treap &other) noexcept;

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

    bool empty() const { return size() == 0; }

    size_type size() const { return _root != nullptr ? _root->size() : 0; }

private:
    template<typename... Args>
    node_holder construct_node(Args &&... args);

private:
    iterator iterator_of_key(const key_type& key);

    const_iterator iterator_of_key(const key_type &key) const;

    treap_node *node_of_order(size_type index);

    const treap_node *node_of_order(size_type index) const;

private:
    iterator const_cast_iterator(const const_iterator& it);

public:
    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;

    reverse_iterator rbegin();

    const_reverse_iterator rbegin() const;

    reverse_iterator rend();

    const_reverse_iterator rend() const;

    const_iterator cbegin() const;

    const_iterator cend() const;

    const_reverse_iterator crbegin() const;

    const_reverse_iterator crend() const;

private:
    static std::mt19937_64 random_generator;
};

template<typename Node, typename Compare, typename Allocator>
std::mt19937_64 Treap<Node, Compare, Allocator>::random_generator(
        std::chrono::steady_clock::now().time_since_epoch().count());

//======================common_iterator implementation==========================================


template<typename Node, typename Compare, typename Allocator>
template<bool B>
Treap<Node, Compare, Allocator>::common_iterator<B>::common_iterator(value_type *value, treap_type* treap,
                                                                    size_type index)
        :_value(value), _treap(treap), _index(index) {}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B> &
Treap<Node, Compare, Allocator>::common_iterator<B>::operator=(const common_iterator<false>& other) {
    if constexpr (!B) {
        if(this == &other) {
            return *this;
        }
    }
    _value = other._value;
    _treap = other._treap;
    _index = other._index;
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B> &
Treap<Node, Compare, Allocator>::common_iterator<B>::operator++() {
    auto *node = _treap->node_of_order(++_index);
    _value = (node == nullptr ? nullptr : node->get_value_address());
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
Treap<Node, Compare, Allocator>::common_iterator<B>::common_iterator(const common_iterator<false>& other)
        :_value(other._value), _treap(other._treap), _index(other._index) {}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B>
Treap<Node, Compare, Allocator>::common_iterator<B>::operator++(int) &{
    common_iterator iter = *this;
    ++(*this);
    return iter;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B> &
Treap<Node, Compare, Allocator>::common_iterator<B>::operator+=(ptrdiff_t n) {
    auto *node = _treap->node_of_order(_index += n);
    _value = (node == nullptr ? nullptr : node->get_value_address());
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B> &
Treap<Node, Compare, Allocator>::common_iterator<B>::operator--() {
    auto *node = _treap->node_of_order(--_index);
    _value = (node == nullptr ? nullptr : node->get_value_address());
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B>
Treap<Node, Compare, Allocator>::common_iterator<B>::operator--(int) &{
    common_iterator iter = *this;
    --(*this);
    return iter;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B> &
Treap<Node, Compare, Allocator>::common_iterator<B>::operator-=(ptrdiff_t n) {
    auto *node = _treap->node_of_order(_index -= n);
    _value = (node == nullptr ? nullptr : node->get_value_address());
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
ptrdiff_t Treap<Node, Compare, Allocator>::common_iterator<B>::operator-(const common_iterator<B> &iter) const {
    return static_cast<ptrdiff_t>(_index) - iter._index;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
auto Treap<Node, Compare, Allocator>::common_iterator<B>::operator*() const -> value_type & {
    return *_value;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
auto Treap<Node, Compare, Allocator>::common_iterator<B>::operator->() const -> value_type * {
    return _value;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
bool Treap<Node, Compare, Allocator>::common_iterator<B>::operator==(const common_iterator<B> &iter) const {
    return _value == iter._value;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
bool Treap<Node, Compare, Allocator>::common_iterator<B>::operator!=(const common_iterator<B> &iter) const {
    return _value != iter._value;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
bool Treap<Node, Compare, Allocator>::common_iterator<B>::operator<(const common_iterator<B> &iter) const {
    return _index < iter._index;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
bool Treap<Node, Compare, Allocator>::common_iterator<B>::operator>(const common_iterator<B> &iter) const {
    return _index > iter._index;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
bool Treap<Node, Compare, Allocator>::common_iterator<B>::operator<=(const common_iterator<B> &iter) const {
    return _index <= iter._index;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
bool Treap<Node, Compare, Allocator>::common_iterator<B>::operator>=(const common_iterator<B> &iter) const {
    return _index >= iter._index;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B>
Treap<Node, Compare, Allocator>::common_iterator<B>::operator+(ptrdiff_t n) {
    common_iterator<B> iter = *this;
    return iter += n;
}

template<typename Node, typename Compare, typename Allocator>
template<bool B>
typename Treap<Node, Compare, Allocator>::template common_iterator<B>
Treap<Node, Compare, Allocator>::common_iterator<B>::operator-(ptrdiff_t n) {
    common_iterator<B> iter = *this;
    return iter -= n;
}

template<typename Node, typename Compare, typename Allocator>
Treap<Node, Compare, Allocator>::Treap(const key_compare &comparator, const allocator_type &allocator)
        : _root(nullptr), _comparator(comparator), _node_allocator(allocator) {}

template<typename Node, typename Compare, typename Allocator>
Treap<Node, Compare, Allocator>::Treap(std::initializer_list<value_type> il, const key_compare &comparator,
                                      const allocator_type &allocator)
        : _root(nullptr), _comparator(comparator), _node_allocator(allocator) {
    for (const auto &value: il) {
        emplace(value);
    }
}

template<typename Node, typename Compare, typename Allocator>
Treap<Node, Compare, Allocator>::Treap(const Treap<Node, Compare, Allocator> &other)
        : _root(nullptr), _comparator(other._comparator), _node_allocator(other._node_allocator) {
    for(auto it = other.begin(); it != other.end(); ++it) {
        insert(*it);
    }
}

template<typename Node, typename Compare, typename Allocator>
Treap<Node, Compare, Allocator>::Treap(Treap<Node, Compare, Allocator> &&other) noexcept
        : _root(std::exchange(other._root, nullptr)), _comparator(std::move(other._comparator)),
          _node_allocator(std::move(other._node_allocator)) {}

template<typename Node, typename Compare, typename Allocator>
Treap<Node, Compare, Allocator> &Treap<Node, Compare, Allocator>::operator=(const Treap<Node, Compare, Allocator> &other) {
    if (this != &other) {
        Treap<Node, Compare, Allocator> copied(other);
        this->swap(copied);
    }
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
Treap<Node, Compare, Allocator> &
Treap<Node, Compare, Allocator>::operator=(Treap<Node, Compare, Allocator> &&other) noexcept {
    if (this != &other) {
        Treap<Node, Compare, Allocator> moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
Treap<Node, Compare, Allocator>::~Treap() {
    destroy_tree(_root);
}

template<typename Node, typename Compare, typename Allocator>
void Treap<Node, Compare, Allocator>::destroy_tree(treap_node *node) {
    if (node != nullptr) {
        // destroy child nodes
        destroy_tree(node->get_left());
        destroy_tree(node->get_right());
        // destroy node key and deallocate memory
        node_holder holder(node, treap_node_destructor(_node_allocator, true));
    }
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::treap_node *
Treap<Node, Compare, Allocator>::merge(treap_node *node1, treap_node *node2) {
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
auto Treap<Node, Compare, Allocator>::split(treap_node *node, const key_type &key) -> std::pair<treap_node*, treap_node*> {
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
void Treap<Node, Compare, Allocator>::swap(Treap<Node, Compare, Allocator> &other) noexcept {
    std::swap(_root, other._root);
    std::swap(_comparator, other._comparator);
}

template<typename Node, typename Compare, typename Allocator>
std::pair<typename Treap<Node, Compare, Allocator>::iterator, bool>
Treap<Node, Compare, Allocator>::insert(const key_type &key) {
    return emplace(key);
}

template<typename Node, typename Compare, typename Allocator>
std::pair<typename Treap<Node, Compare, Allocator>::iterator, bool>
Treap<Node, Compare, Allocator>::insert(key_type &&key) {
    return emplace(std::move(key));
}

template<typename Node, typename Compare, typename Allocator>
template<typename... Args>
std::pair<typename Treap<Node, Compare, Allocator>::iterator, bool>
Treap<Node, Compare, Allocator>::emplace(Args &&... args) {
    // allocate memory for node and construct value
    node_holder holder = construct_node(std::forward<Args>(args)...);
    // if the tree already contains key, then just return
    auto it = find(holder->get_key());
    if (it != end()) {
        // node holder will automatically deallocate memory and destroy value
        return {it, false};
    }
    // initialize non-initialized memory for avoiding segfaults
    holder->set_members(random_generator(), nullptr, nullptr);
    if (_root == nullptr) {
        _root = holder.release();
        return { begin(), true};
    }
    // insert new constructed node into tree
    std::pair<treap_node *, treap_node *> p = split(_root, holder->get_key());
    _root = merge(p.second, merge(p.first, holder.get()));
    // release node holder, as insertion completed successfully
    auto* node = holder.release();
    size_type index = order_of_key(node->get_key());
    return {iterator(node->get_value_address(), this, index), true};
}

template<typename Node, typename Compare, typename Allocator>
template<typename... Args>
typename Treap<Node, Compare, Allocator>::node_holder Treap<Node, Compare, Allocator>::construct_node(Args &&... args) {
    // allocate memory for new node
    node_holder holder(node_traits::allocate(_node_allocator, 1), treap_node_destructor(_node_allocator));
    // construct key using perfect forwarding technique
    node_traits::construct(_node_allocator, holder->get_value_address(), std::forward<Args>(args)...);
    // set value constructed flag true in order to destroy constructed value using deleter
    holder.get_deleter().value_constructed = true;
    return holder;
}

template<typename Node, typename Compare, typename Allocator>
void Treap<Node, Compare, Allocator>::erase(const key_type &key) {
    std::pair<treap_node *, treap_node *> first_split_pair = split(_root, key);
    std::pair<treap_node *, treap_node *> second_split_pair = split<true>(first_split_pair.second, key);
    destroy_tree(second_split_pair.first);
    if (empty()) {
        _root = nullptr;
        return;
    }
    _root = merge(first_split_pair.first, second_split_pair.second);
}

template<typename Node, typename Compare, typename Allocator>
bool Treap<Node, Compare, Allocator>::contains(const key_type &key) const {
    return iterator_of_key(key) != end();
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::iterator
Treap<Node, Compare, Allocator>::find(const key_type &key) {
    return iterator_of_key(key);
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_iterator
Treap<Node, Compare, Allocator>::find(const key_type &key) const {
    return iterator_of_key(key);
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::iterator
Treap<Node, Compare, Allocator>::iterator_of_key(const key_type &key) {
    return const_cast_iterator(const_cast<const Treap*>(this)->iterator_of_key(key));
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_iterator
Treap<Node, Compare, Allocator>::iterator_of_key(const key_type &key) const {
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
typename Treap<Node, Compare, Allocator>::treap_node *Treap<Node, Compare, Allocator>::node_of_order(size_type index) {
    return const_cast<treap_node *>(const_cast<const Treap<Node, Compare, Allocator> *>(this)->node_of_order(index));
}

template<typename Node, typename Compare, typename Allocator>
const typename Treap<Node, Compare, Allocator>::treap_node *
Treap<Node, Compare, Allocator>::node_of_order(size_type index) const {
    if (index == size()) {
        return nullptr;
    }
    if (index > size()) {
        throw std::out_of_range(std::to_string(index) + " index out of bounds");
    }
    ++index;
    treap_node *root = _root;
    while (root != nullptr) {
        size_type left_count = root->left_size();
        if (index == left_count + 1) {
            return root;
        }
        if (index <= left_count) {
            root = root->get_left();
            continue;
        }
        root = root->get_right();
        index -= left_count + 1;
    }
    throw std::runtime_error("Unreachable code");
}
template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::iterator
Treap<Node, Compare, Allocator>::const_cast_iterator(const const_iterator& it) {
    size_type index = it - const_iterator(nullptr, this, 0);
    const value_type& const_value = *it;
    auto* value = const_cast<value_type*>(std::addressof(const_value));
    return {value, this, index};
}

template<typename Node, typename Compare, typename Allocator>
const typename Treap<Node, Compare, Allocator>::key_type &
Treap<Node, Compare, Allocator>::key_of_order(size_type index) const {
    return node_of_order(index)->get_key();
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::size_type
Treap<Node, Compare, Allocator>::order_of_key(const key_type &key) const {
    auto it = iterator_of_key(key);
    // create dummy iterator in order to avoid additional calculations and improve performance
    auto dummy_iterator = const_iterator(nullptr, this, 0);
    return it - dummy_iterator;
}

template<typename Node, typename Compare, typename Allocator>
int Treap<Node, Compare, Allocator>::maxDepth() const {
    return maxDepth(_root);
}

template<typename Node, typename Compare, typename Allocator>
int Treap<Node, Compare, Allocator>::maxDepth(const treap_node *node) const {
    if (node == nullptr) {
        return 0;
    }
    return std::max(maxDepth(node->get_right()), maxDepth(node->get_left())) + 1;
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::iterator Treap<Node, Compare, Allocator>::begin() {
    if (empty()) {
        return end();
    }
    const size_type index = 0;
    return {node_of_order(index)->get_value_address(), this, index};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_iterator Treap<Node, Compare, Allocator>::begin() const {
    return cbegin();
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::iterator Treap<Node, Compare, Allocator>::end() {
    return {nullptr, this, size()};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_iterator Treap<Node, Compare, Allocator>::end() const {
    return cend();
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::reverse_iterator Treap<Node, Compare, Allocator>::rbegin() {
    return {end()};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_reverse_iterator Treap<Node, Compare, Allocator>::rbegin() const {
    return {end()};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::reverse_iterator Treap<Node, Compare, Allocator>::rend() {
    return {begin()};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_reverse_iterator Treap<Node, Compare, Allocator>::rend() const {
    return {begin()};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_iterator Treap<Node, Compare, Allocator>::cbegin() const {
    if (empty()) {
        return cend();
    }
    const size_type index = 0;
    return {node_of_order(index)->get_value_address(), this, index};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_iterator Treap<Node, Compare, Allocator>::cend() const {
    return {nullptr, this, size()};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_reverse_iterator Treap<Node, Compare, Allocator>::crbegin() const {
    return {cend()};
}

template<typename Node, typename Compare, typename Allocator>
typename Treap<Node, Compare, Allocator>::const_reverse_iterator Treap<Node, Compare, Allocator>::crend() const {
    return {cbegin()};
}

