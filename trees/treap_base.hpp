#ifndef BASICS_TREAP_BASE_HPP
#define BASICS_TREAP_BASE_HPP

#include <algorithm>
#include <cstddef>
#include <memory>
#include <chrono>
#include <random>

#include <reverse_iterator.hpp>

namespace nstd {


template <typename Node>
class treap_end_node {
protected:
    using treap_node = Node;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
protected:
    treap_node* _parent = nullptr;

    treap_node* _left = nullptr;

public:
    explicit treap_end_node(treap_node* left = nullptr)
            : _parent(nullptr), _left(left) {}

    treap_end_node(const treap_end_node& other) = default;

    treap_end_node(treap_end_node&& other) noexcept {
        set_left(std::exchange(other._left, nullptr));
    }

    treap_end_node& operator=(const treap_end_node& other) = default;

    treap_end_node& operator=(treap_end_node&& other) noexcept {
        if (this != &other) {
            set_left(std::exchange(other._left, nullptr));
        }
        return *this;
    }

protected:
    explicit treap_end_node(treap_node* parent, treap_node* left)
            : _parent(parent), _left(left) {}

public:
    void set_left(treap_node* left) {
        _left = left;
        if (_left != nullptr) {
            _left->set_parent(static_cast<treap_node*>(this));
        }
    }

    treap_node* get_left() { return _left; }

    const treap_node* get_left() const { return _left; }

    size_type left_size() const { return (_left != nullptr ? _left->size() : 0); }

    size_type size() const { return left_size() + 1; }

    bool is_end_node() const { return _parent == nullptr; }

};

/**
 * Treap node base class
 * Implements basic part of the treap node (left, right child nodes, priority)
 * Serves as base class for all kind of treap nodes
 * Does not have key, value getter functions, as they are different for each data structure
 * @tparam Node Treap node class, which inherits from treap_node_base
 * Template parameter is for avoiding persistent down casts
 */
template <typename Node>
class treap_node_base : public treap_end_node<Node> {
    using base_type = treap_end_node<Node>;
protected:
    using typename base_type::treap_node;
    using typename base_type::size_type;
    using typename base_type::difference_type;
    using priority_type = unsigned long long;

private:
    // node priority presented in integer type
    priority_type _priority;
    // parent node
    using base_type::_parent;
    // left child
    using base_type::_left;
    // right child
    treap_node* _right;
    // size showing how many nodes are lying under tree with root of this node
    size_type _size;

public:
    explicit treap_node_base(priority_type priority = 0, treap_node* left = nullptr,
                             treap_node* right = nullptr, treap_node* parent = nullptr)
            : base_type(parent, left), _priority(priority), _right(right), _size(1) { update(); }

public:
    void set_members(priority_type priority = 0, treap_node* left = nullptr, treap_node* right = nullptr,
                     treap_node* parent = nullptr) {
        _priority = priority;
        _left = left;
        _right = right;
        _parent = parent;
        update();
    }

public:
    void set_left(treap_node* node) {
        base_type::set_left(node);
        update();
    }

    void set_right(treap_node* node) {
        _right = node;
        if (_right != nullptr) {
            _right->set_parent(static_cast<treap_node*>(this));
        }
        update();
    }

    void set_parent(treap_node* node) {
        _parent = node;
    }

    treap_node* get_left() { return _left; }

    const treap_node* get_left() const { return _left; }

    treap_node* get_right() { return _right; }

    const treap_node* get_right() const { return _right; }

    treap_node* get_parent() { return _parent; }

    const treap_node* get_parent() const { return _parent; }

    size_type size() const { return _size; }

    size_type left_size() const { return (_left != nullptr ? _left->_size : 0); }

    size_type right_size() const { return (_right != nullptr ? _right->_size : 0); }

    priority_type get_priority() const { return _priority; }

    using base_type::is_end_node;

public:
    treap_node* next(difference_type offset = 1) { return node_of_offset(offset); }

    const treap_node* next(difference_type offset = 1) const { return node_of_offset(offset); }


    treap_node* prev(difference_type offset = 1) { return node_of_offset(-offset); }

    const treap_node* prev(difference_type offset = 1) const { return node_of_offset(-offset); }

    treap_node* node_of_order(size_type index);

    /**
     * Works with O(log size) complexity
     * @param index order of node
     * @return proper treap node index, when index < size, nullptr when index = size
     * Throws std::out_of_range exception, when index > size
     */
    const treap_node* node_of_order(size_type index) const;

    /**
     * @return The order of the current node in the tree
     */
    size_type order() const;

private:
    treap_node* node_of_offset(difference_type offset);

    /**
     * Gives the node located in the given offset
     * Works with O(log size) complexity
     * @param offset offset
     * @return proper treap node, when there is node with the given offset, nullptr otherwise
     */
    const treap_node* node_of_offset(difference_type offset) const;

private:
    /**
     * Updates size member corresponding to left and right nodes
     */
    void update() { _size = left_size() + right_size() + 1; }
};

/**
* Treap Node destructor class
* Is used as unique pointer destructor class
* @tparam Allocator Treap node allocator class
*/
template <typename Allocator>
class treap_node_destructor {
    using allocator_type = Allocator;
    using allocator_traits = std::allocator_traits<Allocator>;
public:
    using pointer = typename allocator_traits::pointer;
private:
    allocator_type& _allocator;
public:
    bool value_constructed;
public:
    treap_node_destructor(const treap_node_destructor&) = default;

    treap_node_destructor& operator=(const treap_node_destructor&) = delete;

    explicit treap_node_destructor(allocator_type& allocator, bool value_constructed = false) noexcept
            : _allocator(allocator), value_constructed(value_constructed) {}

    /**
     * Destroys underlying value, if it's constructed and deallocates node memory
     * @param node treap node pointer
     */
    void operator()(pointer node) _NOEXCEPT {
        if (value_constructed) {
            allocator_traits::destroy(_allocator, node->get_value_address());
        }
        if (node) {
            allocator_traits::deallocate(_allocator, node, 1);
        }
    }
};

template <typename Node, typename Allocator>
class treap_base {
public:
    using key_type = typename Node::key_type;
    using value_type = typename Node::value_type;
    using allocator_type = Allocator;
    using size_type = size_t;

private:
    using treap_node = Node;
    using end_node_t = treap_end_node<treap_node>;
    using alloc_traits = std::allocator_traits<allocator_type>;
    using node_allocator_type = typename alloc_traits::template rebind_alloc<treap_node>;
    using node_traits = std::allocator_traits<node_allocator_type>;

    using node_destructor = treap_node_destructor<node_allocator_type>;
protected:
    using node_holder = std::unique_ptr<treap_node, node_destructor>;

private:
    /**
     * Iterator class for treap data structure
     * @tparam B determines is iterator class for const elements or not
     */
    template <bool B>
    class common_iterator {
        friend class common_iterator<!B>;

    public:
        using value_type = std::conditional_t<B, const treap_base::value_type, treap_base::value_type>;
        using node_type = std::conditional_t<B, const treap_node, treap_node>;
        using difference_type = ptrdiff_t;
    private:
        node_type* _node;

    public:
        common_iterator(node_type* node);

        /**
         * This constructor serves as copy constructor for iterator
         * And conversion operator from iterator to const_iterator either
         * @param other other object
         */
        common_iterator(const common_iterator<false>& other);

    public:
        common_iterator<B>& operator++();

        common_iterator<B> operator++(int)&;

        common_iterator<B>& operator+=(difference_type n);

        common_iterator<B>& operator--();

        common_iterator<B> operator--(int)&;

        common_iterator<B>& operator-=(difference_type n);

    public:
        difference_type operator-(const common_iterator<B>& other) const;

    public:
        value_type& operator*() const;

        value_type* operator->() const;

    public:
        bool operator==(const common_iterator<B>& other) const;

        bool operator!=(const common_iterator<B>& other) const;

        bool operator<(const common_iterator<B>& other) const;

        bool operator>(const common_iterator<B>& other) const;

        bool operator<=(const common_iterator<B>& other) const;

        bool operator>=(const common_iterator<B>& other) const;

    public:
        common_iterator<B> operator+(difference_type n) const;

        common_iterator<B> operator-(difference_type n) const;

    public:
        size_type order() const;
    };

public:
    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;
    using reverse_iterator = common_reverse_iterator<iterator>;
    using const_reverse_iterator = common_reverse_iterator<const_iterator>;

protected:
    end_node_t _end;
    node_allocator_type _node_allocator;

protected:
    treap_node* root() { return _end.get_left(); }

    const treap_node* root() const { return _end.get_left(); }

    void set_root(treap_node* root) { _end.set_left(root); }

    treap_node* end_node() { return static_cast<treap_node*>(&_end); }

    const treap_node* end_node() const { return static_cast<const treap_node*>(&_end); }

public:
    explicit treap_base(const allocator_type& allocator = allocator_type());

    /**
     * This constructor is created for technical purposes
     * Constructs end node by default
     * Calls node_traits::select_on_container_copy_construction with other allocator
     * @param other
     */
    treap_base(const treap_base& other);

    treap_base(treap_base&& other) noexcept;

    /** In base treap class we already don't know how to insert elements, so copy assignment operator is deleted */
    treap_base& operator=(const treap_base& other) = delete;

    treap_base& operator=(treap_base&& other) noexcept;

    ~treap_base();

protected:
    /**
     * Destroys underlying tree node values and deallocates memory
     * @param node
     */
    void destroy_tree(treap_node* node);

    /**
     * Constructs treap node and it's value with passed constructor arguments
     * Uses perfect forwarding technique
     * @tparam Args constructor argument types
     * @param args constructor arguments
     * @return node holder, i.e. unique_pointer with special destructor class
     */
    template <typename... Args>
    node_holder construct_node(Args&& ... args);

public:
    void swap(treap_base& other) noexcept;

    bool empty() const { return size() == 0; }

    size_type size() const { return _end.left_size(); }

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

protected:
    treap_node* merge_with_index(treap_node* node1, treap_node* node2);

    std::pair<treap_node*, treap_node*> split_with_index(treap_node* node, size_type index);

    treap_node* detach_interval(size_type begin, size_type end);

public:
    /**
     * Erases interval with the passed endpoints from the tree
     * Working complexity is O(end - begin + log size)
     * If end <= begin nothing happens
     * Provides strong exception guarantee
     * @param begin interval begin (inclusive endpoint)
     * @param end interval end (exclusive endpoint)
     */
    void erase_interval(size_type begin, size_type end);

    /**
     * Erases index from the tree
     * Working complexity is O(log size)
     * If index >= size nothing happens
     * Provides strong exception guarantee
     * @param index index to be erased
     */
    void erase_index(size_type index);

    /**
     * Erases iterator from the tree
     * Working complexity is O(log size)
     * Function assumes that iterator belongs to this tree and the behaviour is undefined if not so
     * Provides strong exception guarantee
     * @param it iterator to be erased
     */
    void erase(const_iterator it);

    /**
     * Erases iterator interval from the tree
     * Working complexity is O(end - begin + log size)
     * Function assumes that iterators belong to this tree and the behaviour is undefined if not so
     * Provides strong exception guarantee
     * @param begin begin (inclusive endpoint)
     * @param end end (exclusive endpoint)
     */
    void erase(const_iterator begin, const_iterator end);

protected:
    static std::mt19937_64 random_generator;
};

template <typename Node, typename Allocator>
std::mt19937_64 treap_base<Node, Allocator>::random_generator(
        std::chrono::steady_clock::now().time_since_epoch().count());

//======================common_iterator implementation==========================================


template <typename Node, typename Allocator>
template <bool B>
treap_base<Node, Allocator>::common_iterator<B>::common_iterator(node_type* node)
        :_node(node) {}

template <typename Node, typename Allocator>
template <bool B>
treap_base<Node, Allocator>::common_iterator<B>::common_iterator(const common_iterator<false>& other)
        :_node(other._node) {}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::template common_iterator<B>&
treap_base<Node, Allocator>::common_iterator<B>::operator++() {
    _node = _node->next();
    return *this;
}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::template common_iterator<B>
treap_base<Node, Allocator>::common_iterator<B>::operator++(int)& {
    common_iterator iter = *this;
    ++(*this);
    return iter;
}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::template common_iterator<B>&
treap_base<Node, Allocator>::common_iterator<B>::operator+=(difference_type n) {
    _node = _node->next(n);
    return *this;
}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::template common_iterator<B>&
treap_base<Node, Allocator>::common_iterator<B>::operator--() {
    _node = _node->prev();
    return *this;
}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::template common_iterator<B>
treap_base<Node, Allocator>::common_iterator<B>::operator--(int)& {
    common_iterator iter = *this;
    --(*this);
    return iter;
}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::template common_iterator<B>&
treap_base<Node, Allocator>::common_iterator<B>::operator-=(difference_type n) {
    _node = _node->prev(n);
    return *this;
}

template <typename Node, typename Allocator>
template <bool B>
auto
treap_base<Node, Allocator>::common_iterator<B>::operator-(const common_iterator<B>& other) const -> difference_type {
    return static_cast<difference_type>(_node->order()) - other._node->order();
}

template <typename Node, typename Allocator>
template <bool B>
auto treap_base<Node, Allocator>::common_iterator<B>::operator*() const -> value_type& {
    return _node->get_value();
}

template <typename Node, typename Allocator>
template <bool B>
auto treap_base<Node, Allocator>::common_iterator<B>::operator->() const -> value_type* {
    return _node->get_value_address();
}

template <typename Node, typename Allocator>
template <bool B>
bool treap_base<Node, Allocator>::common_iterator<B>::operator==(const common_iterator<B>& other) const {
    return _node == other._node;
}

template <typename Node, typename Allocator>
template <bool B>
bool treap_base<Node, Allocator>::common_iterator<B>::operator!=(const common_iterator<B>& other) const {
    return _node != other._node;
}

template <typename Node, typename Allocator>
template <bool B>
bool treap_base<Node, Allocator>::common_iterator<B>::operator<(const common_iterator<B>& other) const {
    return _node->order() < other._node->order();
}

template <typename Node, typename Allocator>
template <bool B>
bool treap_base<Node, Allocator>::common_iterator<B>::operator>(const common_iterator<B>& other) const {
    return _node->order() > other._node->order();
}

template <typename Node, typename Allocator>
template <bool B>
bool treap_base<Node, Allocator>::common_iterator<B>::operator<=(const common_iterator<B>& other) const {
    return _node->order() <= other._node->order();
}

template <typename Node, typename Allocator>
template <bool B>
bool treap_base<Node, Allocator>::common_iterator<B>::operator>=(const common_iterator<B>& other) const {
    return _node->order() >= other._node->order();
}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::template common_iterator<B>
treap_base<Node, Allocator>::common_iterator<B>::operator+(difference_type n) const {
    common_iterator<B> iter = *this;
    return iter += n;
}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::template common_iterator<B>
treap_base<Node, Allocator>::common_iterator<B>::operator-(difference_type n) const {
    common_iterator<B> iter = *this;
    return iter -= n;
}

template <typename Node, typename Allocator>
template <bool B>
typename treap_base<Node, Allocator>::size_type
treap_base<Node, Allocator>::common_iterator<B>::order() const {
    return _node->order();
}

//==========================================Treap base implementation==========================================

template <typename Node, typename Allocator>
treap_base<Node, Allocator>::treap_base(const allocator_type& allocator)
        : _end(), _node_allocator(allocator) {}

template <typename Node, typename Allocator>
treap_base<Node, Allocator>::treap_base(const treap_base& other)
        : _end(), _node_allocator(node_traits::select_on_container_copy_construction(other._node_allocator)) {}

template <typename Node, typename Allocator>
treap_base<Node, Allocator>::treap_base(treap_base&& other) noexcept
        : _end(std::move(other._end)),
          _node_allocator(std::move(other._node_allocator)) {}

template <typename Node, typename Allocator>
treap_base<Node, Allocator>&
treap_base<Node, Allocator>::operator=(treap_base&& other) noexcept {
    if (this != &other) {
        treap_base moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template <typename Node, typename Allocator>
treap_base<Node, Allocator>::~treap_base() {
    destroy_tree(root());
}

template <typename Node, typename Allocator>
void treap_base<Node, Allocator>::destroy_tree(treap_node* node) {
    if (node != nullptr) {
        // destroy child nodes
        destroy_tree(node->get_left());
        destroy_tree(node->get_right());
        // destroy node key and deallocate memory
        node_holder holder(node, treap_node_destructor(_node_allocator, true));
    }
}

template <typename Node, typename Allocator>
void treap_base<Node, Allocator>::swap(treap_base& other) noexcept {
    std::swap(_end, other._end);
    std::swap(_node_allocator, other._node_allocator);
}

template <typename Node, typename Allocator>
template <typename... Args>
typename treap_base<Node, Allocator>::node_holder treap_base<Node, Allocator>::construct_node(Args&& ... args) {
    // allocate memory for new node
    node_holder holder(node_traits::allocate(_node_allocator, 1), treap_node_destructor(_node_allocator));
    // construct key using perfect forwarding technique
    node_traits::construct(_node_allocator, holder->get_value_address(), std::forward<Args>(args)...);
    // set value constructed flag true in order to destroy constructed value using deleter
    holder.get_deleter().value_constructed = true;
    // initialize non-initialized memory for avoiding segfaults
    holder->set_members(random_generator(), nullptr, nullptr, nullptr);
    return holder;
}

template <typename Node>
typename treap_node_base<Node>::treap_node* treap_node_base<Node>::node_of_offset(difference_type offset) {
    return const_cast<treap_node*>(const_cast<const treap_node_base*>(this)->node_of_offset(offset));
}

template <typename Node>
const typename treap_node_base<Node>::treap_node* treap_node_base<Node>::node_of_offset(difference_type offset) const {
    const auto* root = static_cast<const treap_node*>(this);
    ptrdiff_t index = left_size() + offset;
    while (root != nullptr) {
        if (0 <= index && index < root->size()) {
            return root->node_of_order(index);
        }
        const treap_node* parent = root->get_parent();
        if (parent->get_right() == root) {
            index += parent->left_size() + 1;
        }
        root = parent;
    }
    return nullptr;
}

template <typename Node>
typename treap_node_base<Node>::treap_node* treap_node_base<Node>::node_of_order(size_type index) {
    return const_cast<treap_node*>(const_cast<const treap_node_base<Node>*>(this)->node_of_order(index));
}

template <typename Node>
const typename treap_node_base<Node>::treap_node* treap_node_base<Node>::node_of_order(size_type index) const {
    ++index;
    const auto* root = static_cast<const treap_node*>(this);
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

template <typename Node>
typename treap_node_base<Node>::size_type treap_node_base<Node>::order() const {
    const auto* node = static_cast<const treap_node*>(this);
    bool is_left = true;
    size_type index = left_size();
    while (!node->is_end_node()) {
        if (!is_left) {
            index += 1 + node->left_size();
        }
        is_left = node->_parent->_left == node;
        node = node->_parent;
    }
    return index;
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::iterator treap_base<Node, Allocator>::begin() {
    return {end_node()->node_of_order(0)};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::const_iterator treap_base<Node, Allocator>::begin() const {
    return cbegin();
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::iterator treap_base<Node, Allocator>::end() {
    return {end_node()};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::const_iterator treap_base<Node, Allocator>::end() const {
    return cend();
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::reverse_iterator treap_base<Node, Allocator>::rbegin() {
    return {end()};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::const_reverse_iterator treap_base<Node, Allocator>::rbegin() const {
    return {end()};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::reverse_iterator treap_base<Node, Allocator>::rend() {
    return {begin()};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::const_reverse_iterator treap_base<Node, Allocator>::rend() const {
    return {begin()};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::const_iterator treap_base<Node, Allocator>::cbegin() const {
    return {end_node()->node_of_order(0)};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::const_iterator treap_base<Node, Allocator>::cend() const {
    return {end_node()};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::const_reverse_iterator treap_base<Node, Allocator>::crbegin() const {
    return {cend()};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::const_reverse_iterator treap_base<Node, Allocator>::crend() const {
    return {cbegin()};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::treap_node*
treap_base<Node, Allocator>::merge_with_index(treap_node* node1, treap_node* node2) {
    if (node1 == nullptr) {
        return node2;
    }
    if (node2 == nullptr) {
        return node1;
    }
    if (node1->get_priority() > node2->get_priority()) {
        node1->set_right(merge_with_index(node1->get_right(), node2));
        return node1;
    }
    node2->set_left(merge_with_index(node1, node2->get_left()));
    return node2;
}

template <typename Node, typename Allocator>
auto
treap_base<Node, Allocator>::split_with_index(treap_node* node, size_type index) -> std::pair<treap_node*, treap_node*> {
    if (node == nullptr || index <= 0) {
        return std::make_pair(nullptr, node);
    }
    if (index >= node->size()) {
        return std::make_pair(node, nullptr);
    }
    if (node->left_size() < index) {
        auto [first, second] = split_with_index(node->get_right(), index - node->left_size() - 1);
        node->set_right(first);
        // return separated nodes
        return {node, second};
    }
    auto [first, second] = split_with_index(node->get_left(), index);
    node->set_left(second);
    // return separated nodes
    return {first, node};
}

template <typename Node, typename Allocator>
typename treap_base<Node, Allocator>::treap_node*
treap_base<Node, Allocator>::detach_interval(size_type begin, size_type end) {
    if (end <= begin) {
        return nullptr;
    }
    auto [left, included_begin] = split_with_index(root(), begin);
    auto [interval, right] = split_with_index(included_begin, end - begin);
    set_root(merge_with_index(left, right));
    return interval;
}

template <typename Node, typename Allocator>
void treap_base<Node, Allocator>::erase_interval(size_type begin, size_type end) {
    auto* interval = detach_interval(begin, end);
    // erase the interval
    destroy_tree(interval);
}

template <typename Node, typename Allocator>
void treap_base<Node, Allocator>::erase_index(size_type index) {
    erase_interval(index, index + 1);
}

template <typename Node, typename Allocator>
void treap_base<Node, Allocator>::erase(const_iterator it) {
    erase(it.order());
}

template <typename Node, typename Allocator>
void treap_base<Node, Allocator>::erase(const_iterator begin, const_iterator end) {
    erase_interval(begin.order(), end.order());
}

} // namespace nstd

#endif //BASICS_TREAP_BASE_HPP