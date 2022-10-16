#include "treap.h"
#include <chrono>
#include <random>

TreapNode *TreapNode::copy() const {
    auto *root = new TreapNode(key, _priority);
    if (_left != nullptr) {
        root->setLeft(_left->copy());
    }
    if (_right != nullptr) {
        root->setRight(_right->copy());
    }
    return root;
}

TreapNode *TreapNode::merge(TreapNode *node1, TreapNode *node2) {
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

std::pair<TreapNode *, TreapNode *> TreapNode::split(TreapNode *node, const value_type &value) {
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

Treap::Treap()
        : _root(nullptr) {}

Treap::Treap(const Treap &other)
        : _root(other._root->copy()) {}

Treap::Treap(Treap &&other) noexcept
        : _root(std::exchange(other._root, nullptr)) {}

Treap &Treap::operator=(const Treap &other) {
    if (this != &other) {
        Treap copied(other);
        swap(copied);
    }
    return *this;
}

Treap &Treap::operator=(Treap &&other) noexcept {
    if (this != &other) {
        Treap moved(std::move(other));
        swap(moved);
    }
    return *this;
}

Treap::~Treap() {
    deallocate(_root);
}

void Treap::swap(Treap &other) noexcept {
    std::swap(_root, other._root);
}

void Treap::insert(const value_type &value) {
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

void Treap::remove(const value_type &value) {
    std::pair<TreapNode *, TreapNode *> first_split_pair = TreapNode::split(_root, value);
    std::pair<TreapNode *, TreapNode *> second_split_pair = TreapNode::split(first_split_pair.second, value + 1);
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

bool Treap::contains(const value_type &value) const {
    return nodeOfKey(value) != nullptr;
}

TreapNode *Treap::nodeOfKey(const value_type &value) {
    return const_cast<TreapNode *>(const_cast<const Treap *>(this)->nodeOfKey(value));
}

const TreapNode *Treap::nodeOfKey(const value_type &value) const {
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

TreapNode *Treap::nodeOfOrder(size_t index) {
    return const_cast<TreapNode *>(const_cast<const Treap *>(this)->nodeOfOrder(index));
}

const TreapNode *Treap::nodeOfOrder(size_t index) const {
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

const TreapNode::value_type &Treap::keyOfOrder(size_t index) const {
    return nodeOfOrder(index)->key;
}

size_t Treap::orderOfKey(const value_type &key) const {
    return orderOfKey(key, _root) - 1;
}

size_t Treap::orderOfKey(const value_type &key, const TreapNode *root) const {
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

void Treap::deallocate(TreapNode *node) {
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


int Treap::maxDepth() const {
    return maxDepth(_root);
}

int Treap::maxDepth(const TreapNode *node) const {
    if (node == nullptr) {
        return 0;
    }
    return std::max(maxDepth(node->getRight()), maxDepth(node->getLeft())) + 1;
}

Treap::iterator Treap::begin() const {
    return cbegin();
}

Treap::iterator Treap::end() const {
    return cend();
}

Treap::reverse_iterator Treap::rbegin() const {
    return {end()};
}

Treap::reverse_iterator Treap::rend() const {
    return {begin()};
}

Treap::const_iterator Treap::cbegin() const {
    if (empty()) {
        return cend();
    }
    const size_t index = 0;
    return {&nodeOfOrder(index)->key, *this, index};
}

Treap::const_iterator Treap::cend() const {
    return {nullptr, *this, size()};
}

Treap::const_reverse_iterator Treap::crbegin() const {
    return {cend()};
}

Treap::const_reverse_iterator Treap::crend() const {
    return {cbegin()};
}
