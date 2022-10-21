#ifndef BASICS_TREAP_H
#define BASICS_TREAP_H

#include <utility>
#include <memory>
#include <chrono>
#include <random>
#include <stack>
#include <treap_base.h>

namespace nstd {

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
    explicit treap(const key_compare &comparator = key_compare(),
                   const allocator_type &allocator = allocator_type());

    treap(const treap &other);

    treap(treap &&other) noexcept;

    treap &operator=(const treap &other);

    treap &operator=(treap &&other) noexcept;

    ~treap() = default;

private:

    /**
     * Merges two nodes into one node
     * Working complexity is O(log size)
     * Provides strong exception safety
     * @param node1 node1
     * @param node2 node2
     * @return merged node, in case of one of the passed node is nullptr, will be returned second one
     */
    treap_node *merge(treap_node *node1, treap_node *node2);

    /**
     * Splits passed node into two nodes with the given key
     * Working complexity is O(log size)
     * Provides strong exception safety
     *
     * @tparam KeyIncluded In case of KeyIncluded parameter is true, node having passed key will be in left tree, in the right otherwise
     * @param node splittable node
     * @param key key to be seperated with
     * @return node pair, where the first tree will consist of nodes, where key is less than passed key
     *         And the second tree will consist of nodes, where key is greater than passed key
     *         The node having passed key will be one of this two trees depending on KeyIncluded template parameter
     */
    template<bool KeyIncluded = false>
    std::pair<treap_node *, treap_node *> split(treap_node *node, const key_type &key);

public:
    void swap(treap &other) noexcept;

    std::pair<iterator, bool> insert(const key_type &key);

    std::pair<iterator, bool> insert(key_type &&key);

    /**
     * Inserts a node in the tree with the key constructed with passed arguments
     * If the key already exists, key will not be inserted
     * Working complexity is O (log size)
     * Provides weak exception safety in case of comparator comparison throws exception
     * @param key key
     * @return pair, where the first one is inserted iterator and the second one is boolean showing whether the key was actually inserted or not
     */
    template<typename... Args>
    std::pair<iterator, bool> emplace(Args &&... args);

    /**
     * Erases the node with the passed key
     * If there is no node having passed key, then nothing happens
     * Working complexity is O (log size)
     * Provides weak exception safety in case of comparator comparison throws exception
     * @param key
     */
    void erase(const key_type &key);

    bool contains(const key_type &key) const;

    /**
     * Returns iterator with the passed key
     * Returns end iterator with the key wasn't found
     * @param key
     * @return
     */
    iterator find(const key_type &key);

    const_iterator find(const key_type &key) const;

    /**
     * Returns the key, which is located in the passed index
     * Works in O (log size) complexity
     * @param index index
     * @return proper key when index < size
     * Throws std::out_of_range exception otherwise
     */
    const key_type &key_of_order(size_type index) const;

    /**
     * Returns index of the passed key
     * Works in O (log size) complexity
     * @param key key
     * @return proper index, when the tree has the key, size() otherwise
     */
    size_type order_of_key(const key_type &key) const;

    using _base::size;

    using _base::empty;

private:
    /**
     * Returns iterator with the passed key
     * Works in O (log size) complexity
     * @param key key
     * @return proper iterator, when the tree has the key, end iterator otherwise
     */
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
        treap copied(other);
        this->swap(copied);
    }
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
treap<Node, Compare, Allocator> &
treap<Node, Compare, Allocator>::operator=(treap &&other) noexcept {
    if (this != &other) {
        treap moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template<typename Node, typename Compare, typename Allocator>
typename treap<Node, Compare, Allocator>::treap_node *
treap<Node, Compare, Allocator>::merge(treap_node *node1, treap_node *node2) {
    // return nullptr when both values are null pointers
    if(node1 == nullptr && node2 == nullptr) {
        return nullptr;
    }

    // stack for collecting node values
    std::stack<treap_node *> nodes;
    // stack for collecting priority comparisons
    std::stack<bool> compares;
    while(node1 != nullptr && node2 != nullptr) {
        // after this operator we can suppose that node1.key <= node2.key
        if (_comparator(node2->get_key(), node1->get_key())) {
            std::swap(node1, node2);
        }
        // save comparison result in stack
        bool compare = node1->get_priority() > node2->get_priority();
        compares.push(compare);
        // save corresponding node and update node1 and node2
        if (compare) {
            nodes.push(node1);
            node1 = node1->get_right();
            continue;
        }
        nodes.push(node2);
        node2 = node2->get_left();
    }
    // child will be non-null node among node1 and node2
    treap_node* child = (node1 == nullptr ? node2 : node1);
    // child will be the last merge result
    while (!compares.empty()){
        // parent of the child node
        treap_node* parent_node = nodes.top();
        nodes.pop();
        // comparison result
        bool compare = compares.top();
        compares.pop();
        // merge parent_node with child
        if (compare) {
            parent_node->set_right(child);
            child = parent_node;
            continue;
        }
        parent_node->set_left(child);
        child = parent_node;
    }

    return child;
}

template<typename Node, typename Compare, typename Allocator>
template<bool KeyIncluded>
auto
treap<Node, Compare, Allocator>::split(treap_node *node,
                                       const key_type &key) -> std::pair<treap_node *, treap_node *> {
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
    if (index >= size()) {
        throw std::out_of_range("Index is out of bounds");
    }
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

} // namespace nstd

#endif // BASICS_TREAP_H
