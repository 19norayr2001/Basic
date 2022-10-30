#ifndef BASICS_IMPLICIT_TREAP_BASE_H
#define BASICS_IMPLICIT_TREAP_BASE_H

#include <utility>
#include <treap_base.hpp>

namespace nstd {

template <typename T>
class implicit_treap_node : public treap_node_base<implicit_treap_node<T>> {
private:
    using base_type = treap_node_base<implicit_treap_node<T>>;
    using typename base_type::priority_type;
    using typename base_type::size_type;
public:
    using value_type = T;
    using raw_value_type = value_type;
public:
    explicit implicit_treap_node(const value_type& value, priority_type priority = 0,
                                 implicit_treap_node* left = nullptr,
                                 implicit_treap_node* right = nullptr,
                                 implicit_treap_node* parent = nullptr)
            : base_type(priority, left, right), _value(value) {}

    const value_type* get_value_address() const { return std::addressof(_value); }

    value_type* get_value_address() { return std::addressof(_value); }

    value_type& get_value() { return _value; }

    const value_type& get_value() const { return _value; }

private:
    value_type _value;
};

template <typename T, typename Allocator>
class implicit_treap : public treap_base<implicit_treap_node<T>, Allocator> {
    using base_type = treap_base<implicit_treap_node<T>, Allocator>;
    using treap_node = implicit_treap_node<T>;
public:
    using typename base_type::value_type;
    using typename base_type::allocator_type;
    using typename base_type::size_type;

private:
    using typename base_type::node_holder;

private:
    using base_type::_end;
    using base_type::root;
    using base_type::set_root;
    using base_type::_begin;

public:
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

public:
    explicit implicit_treap(const allocator_type& allocator = allocator_type());

    implicit_treap(const implicit_treap& other);

    implicit_treap(implicit_treap&& other) noexcept;

    implicit_treap& operator=(const implicit_treap& other);

    implicit_treap& operator=(implicit_treap&& other) noexcept;

    ~implicit_treap() = default;

public:
    iterator insert(const value_type& value, size_type index);

    iterator insert(value_type&& value, size_type index);

    iterator push_back(const value_type& value);

    iterator push_back(value_type&& value);

    template <typename... Args>
    iterator emplace_back(Args&& ... args);

    iterator push_front(const value_type& value);

    iterator push_front(value_type&& value);

    template <typename... Args>
    iterator emplace_front(Args&& ... args);

    using base_type::erase_interval;
    using base_type::erase_index;
    using base_type::erase;

    void pop_back();

    void pop_front();

    value_type& operator[](size_type index);

    const value_type& operator[](size_type index) const;

public:
    /**
     * Exchanges intervals not depending on interval lengths
     * Works in O (log size) complexity
     * If end1 or end2 > size, function will change them with size
     * If begin1 > end1 or begin2 > end2 nothing happens
     * If intervals intersects, nothing happens
     * @param begin1 begin of first interval (inclusive endpoint)
     * @param end1 end of first interval (exclusive endpoint)
     * @param begin2 begin of second interval (inclusive endpoint)
     * @param end2 end of second interval (exclusive endpoint)
     */
    void exchange_intervals(size_type begin1, size_type end1, size_type begin2, size_type end2) noexcept;

    /**
     * Calls exchange_intervals for indexes
     * Passed iterators remain showing at the same elements, which they were showing before function call
     * @param begin begin
     * @param end end
     * @param count shift count
     */
    void exchange_intervals(const_iterator begin1, const_iterator end1,
                            const_iterator begin2, const_iterator end2) noexcept;

    /**
     * Moves passed interval to the index not depending on interval length
     * Works in O (log size) complexity
     * If begin >= end nothing happens
     * If index > size, functions change it with size
     * If index belongs to passed interval, nothing happens
     * @param begin begin (inclusive endpoint)
     * @param end end (exclusive endpoint)
     * @param index index to be moved interval
     */
    void move_interval_to_index(size_type begin, size_type end, size_type index) noexcept;

    /**
     * Calls move_interval_to_index for indexes
     * Passed iterators remain showing at the same elements, which they were showing before function call
     * @param begin begin
     * @param end end
     * @param count shift count
     */
    void move_interval_to_index(const_iterator begin, const_iterator end, const_iterator it) noexcept;

    /**
     * Shifts vector content with the passed count
     * Works in O (log size) complexity non-depending on interval size
     * @param count shift count
     */
    void shift(size_type count = 1) noexcept;

    implicit_treap& operator>>=(size_type count) noexcept;

    /**
     * Shifts vector interval content with the passed count
     * Works in O (log size) complexity non-depending on interval size
     * @param begin interval begin (inclusive endpoint)
     * @param end interval end (exclusive endpoint)
     * @param count shift count
     */
    void shift_interval(size_type begin, size_type end, size_type count = 1) noexcept;

    /**
     * Calls shift_interval for indexes
     * Passed iterators remain showing at the same elements, which they were showing before function call
     * @param begin begin
     * @param end end
     * @param count shift count
     */
    void shift_interval(const_iterator begin, const_iterator end, size_type count = 1) noexcept;

    /**
     * Reverse shifts vector content with the passed count
     * Works in O (log size) complexity non-depending on interval size
     * @param count shift count
     */
    void reverse_shift(size_type count = 1) noexcept;

    implicit_treap& operator<<=(size_type count) noexcept;

    /**
     * Reverse shifts vector interval content with the passed count
     * Works in O (log size) complexity non-depending on interval size
     * @param begin interval begin (inclusive endpoint)
     * @param end interval end (exclusive endpoint)
     * @param count shift count
     */
    void reverse_shift_interval(size_type begin, size_type end, size_type count = 1) noexcept;

    /**
     * Calls reverse_shift_interval for indexes
     * Passed iterators remain showing at the same elements, which they were showing before function call
     * @param begin begin
     * @param end end
     * @param count shift count
     */
    void reverse_shift_interval(const_iterator begin, const_iterator end, size_type count = 1) noexcept;

public:
    using base_type::size;

    using base_type::empty;

private:
    template <typename... Args>
    iterator emplace(size_type index, Args&& ... args);


private:
    using base_type::merge_with_index;
    using base_type::split_with_index;

    /**
     * Using split and merge functions
     * Inserts node in the tree with passed index
     * @param tree node to be inserted
     * @param index index
     * @return iterator pointing inserted node
     */
    iterator insert_tree_at(treap_node* tree, size_type index);
};

template <typename Node, typename Allocator>
implicit_treap<Node, Allocator>::implicit_treap(const allocator_type& allocator)
        : base_type(allocator) {}

template <typename Node, typename Allocator>
implicit_treap<Node, Allocator>::implicit_treap(const implicit_treap& other)
        : base_type(other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        emplace_back(*it);
    }
}

template <typename Node, typename Allocator>
implicit_treap<Node, Allocator>::implicit_treap(implicit_treap&& other) noexcept
        : base_type(std::move(other)) {}

template <typename Node, typename Allocator>
implicit_treap<Node, Allocator>&
implicit_treap<Node, Allocator>::operator=(const implicit_treap& other) {
    if (this != &other) {
        implicit_treap copied(other);
        this->swap(copied);
    }
    return *this;
}

template <typename Node, typename Allocator>
implicit_treap<Node, Allocator>&
implicit_treap<Node, Allocator>::operator=(implicit_treap&& other) noexcept {
    if (this != &other) {
        implicit_treap moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template <typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator
implicit_treap<T, Allocator>::insert_tree_at(treap_node* tree, size_type index) {
    if (tree == nullptr) {
        return base_type::end();
    }
    auto [left, right] = split_with_index(root(), index);
    treap_node* root = merge_with_index(merge_with_index(left, tree), right);
    set_root(root);
    if (index == 0) {
        return {_begin = tree->find_begin()};
    }
    return {tree->find_begin()};
}

template <typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator
implicit_treap<T, Allocator>::insert(const value_type& value, size_type index) {
    return emplace(index, value);
}

template <typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator
implicit_treap<T, Allocator>::insert(value_type&& value, size_type index) {
    return emplace(index, value);
}

template <typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::push_back(const value_type& value) {
    return emplace_back(value);
}

template <typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::push_back(value_type&& value) {
    return emplace_back(value);
}

template <typename T, typename Allocator>
template <typename ...Args>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::emplace_back(Args&& ...args) {
    return emplace(size(), std::forward<Args>(args)...);
}

template <typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::push_front(const value_type& value) {
    return emplace_front(value);
}

template <typename T, typename Allocator>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::push_front(value_type&& value) {
    return emplace_front(value);
}

template <typename T, typename Allocator>
template <typename ...Args>
typename implicit_treap<T, Allocator>::iterator implicit_treap<T, Allocator>::emplace_front(Args&& ...args) {
    return emplace(0, std::forward<Args>(args)...);
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::pop_back() {
    erase(size() - 1);
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::pop_front() {
    erase(0);
}

template <typename T, typename Allocator>
typename implicit_treap<T, Allocator>::value_type& implicit_treap<T, Allocator>::operator[](size_type index) {
    return *(base_type::begin() + index);
}

template <typename T, typename Allocator>
const typename implicit_treap<T, Allocator>::value_type&
implicit_treap<T, Allocator>::operator[](size_type index) const {
    return *(base_type::cbegin() + index);
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::exchange_intervals(size_type begin1, size_type end1,
                                                      size_type begin2, size_type end2) noexcept {
    end1 = std::min(end1, size());
    end2 = std::min(end2, size());
    if (begin1 > end1 || begin2 > end2) {
        return;
    }
    if (begin1 > begin2) {
        std::swap(begin1, begin2);
        std::swap(end1, end2);
    }
    // here we have that begin1 <= begin2
    // check whether the intervals intersect or not
    if (end1 > begin2) {
        // interval intersects, then just return
        return;
    }
    // detach intervals from the tree
    auto* interval2 = base_type::detach_interval(begin2, end2);
    auto* interval1 = base_type::detach_interval(begin1, end1);
    // insert second interval in first interval's place
    insert_tree_at(interval2, begin1);
    // insert first interval in second interval's place
    insert_tree_at(interval1, begin2 + (end2 - begin2) - (end1 - begin1));
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::exchange_intervals(const_iterator begin1, const_iterator end1,
                                                      const_iterator begin2, const_iterator end2) noexcept {
    exchange_intervals(begin1.order(), end1.order(), begin2.order(), end2.order());
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::move_interval_to_index(size_type begin, size_type end, size_type index) noexcept {
    exchange_intervals(begin, end, index, index);
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::move_interval_to_index(const_iterator begin, const_iterator end,
                                                          const_iterator it) noexcept {
    exchange_intervals(begin, end, it, it);
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::shift(size_type count) noexcept {
    shift_interval(0, size(), count);
}

template <typename T, typename Allocator>
implicit_treap<T, Allocator>& implicit_treap<T, Allocator>::operator>>=(size_type count) noexcept {
    shift(count);
    return *this;
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::shift_interval(size_type begin, size_type end, size_type count) noexcept {
    if (begin >= end) {
        return;
    }
    count %= end - begin;
    if (count == 0) {
        return;
    }
    exchange_intervals(begin, end - count, end - count, end);
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::shift_interval(const_iterator begin, const_iterator end, size_type count) noexcept {
    shift_interval(begin.order(), end.order(), count);
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::reverse_shift(size_type count) noexcept {
    reverse_shift_interval(0, size(), count);
}

template <typename T, typename Allocator>
implicit_treap<T, Allocator>& implicit_treap<T, Allocator>::operator<<=(size_type count) noexcept {
    reverse_shift(count);
    return *this;
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::reverse_shift_interval(size_type begin, size_type end, size_type count) noexcept {
    if (begin >= end) {
        return;
    }
    count %= end - begin;
    if (count == 0) {
        return;
    }
    exchange_intervals(begin, begin + count, begin + count, end);
}

template <typename T, typename Allocator>
void implicit_treap<T, Allocator>::reverse_shift_interval(const_iterator begin, const_iterator end,
                                                          size_type count) noexcept {
    reverse_shift_interval(begin.order(), end.order(), count);
}

template <typename T, typename Allocator>
template <typename ...Args>
typename implicit_treap<T, Allocator>::iterator
implicit_treap<T, Allocator>::emplace(size_type index, Args&& ...args) {
    if (index > size()) {
        index = size();
    }
    // allocate memory for node and construct value
    node_holder holder = base_type::construct_node(std::forward<Args>(args)...);
    // insert new constructed node into tree
    auto it = insert_tree_at(holder.get(), index);
    // release node holder, as insertion completed successfully
    holder.release();
    return it;
}

} // namespace nstd

#endif // BASICS_IMPLICIT_TREAP_BASE_H