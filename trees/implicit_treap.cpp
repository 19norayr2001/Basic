#include "implicit_treap.h"
#include <algorithm>
#include <chrono>
#include <random>

ImplicitTreapNode* ImplicitTreapNode::merge(ImplicitTreapNode* node1, ImplicitTreapNode* node2) {
	if (node1 == nullptr) {
		return node2;
	}
	if (node2 == nullptr) {
		return node1;
	}
	ImplicitTreapNode* ret{};
	if (node1->mPriority > node2->mPriority) {
		ret = new ImplicitTreapNode(node1->getValue(), node1->mPriority, node1->getLeft());
        ret->setRight(merge(node1->getRight(), node2));
		delete node1;
	}
	else {
		ret = new ImplicitTreapNode(node2->getValue(), node2->mPriority, nullptr, node2->getRight());
        ret->setLeft(merge(node1, node2->getLeft()));
		delete node2;
	}
	return ret;
}

std::pair<ImplicitTreapNode*, ImplicitTreapNode*> ImplicitTreapNode::split(ImplicitTreapNode* node, size_t x) {
	if (node == nullptr || x <= 0) {
		return std::make_pair(nullptr, node);
	}
	if (x >= node->size()) {
		return std::make_pair(node, nullptr);
	}
	ImplicitTreapNode* retleft{}, * retright{};
	if (node->leftSize() < x) {
		std::pair<ImplicitTreapNode*, ImplicitTreapNode*> pright = ImplicitTreapNode::split(node->getRight(), x - node->leftSize() - 1);
		retleft = node;
        node->setRight(pright.first);
		retright = pright.second;
	}
	else {
		std::pair<ImplicitTreapNode*, ImplicitTreapNode*> pleft = ImplicitTreapNode::split(node->getLeft(), x);
		retleft = pleft.first;
		retright = node;
        retright->setLeft(pleft.second);
	}
	return std::make_pair(retleft, retright);
}

ImplicitTreap::ImplicitTreap()
	: mRoot(nullptr)
{}

ImplicitTreap::~ImplicitTreap() {
	deallocate(mRoot);
}

void ImplicitTreap::pushBack(const int& value) {
	insert(value, size());
}

void ImplicitTreap::insert(const int& value, size_t ind) {
	static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	auto* my_node = new ImplicitTreapNode(value, rng() % (1ll << 31));
	if (mRoot == nullptr) {
		mRoot = my_node;
		return;
	}
	std::pair<ImplicitTreapNode*, ImplicitTreapNode*> p = ImplicitTreapNode::split(mRoot, ind);
	mRoot = ImplicitTreapNode::merge(ImplicitTreapNode::merge(p.first, my_node), p.second);
}

void ImplicitTreap::remove(size_t ind) {
	std::pair<ImplicitTreapNode*, ImplicitTreapNode*> first_split_pair = ImplicitTreapNode::split(mRoot, ind);
	std::pair<ImplicitTreapNode*, ImplicitTreapNode*> second_split_pair = ImplicitTreapNode::split(first_split_pair.second, 1);
	if (second_split_pair.first == nullptr) {
		throw std::runtime_error("Element not found");
	}
	delete second_split_pair.first;
	if (empty()) {
		mRoot = nullptr;
		return;
	}
	mRoot = ImplicitTreapNode::merge(first_split_pair.first, second_split_pair.second);
}

int ImplicitTreap::keyOfOrder(size_t ind) const {
	if (ind >= size()) {
		throw std::out_of_range("Index out of bounds");
	}
	ind++;
	return keyOfOrder(ind, mRoot);
}

int ImplicitTreap::keyOfOrder(size_t ind, ImplicitTreapNode* root) const {
	size_t leftcount = root->leftSize();
	if (leftcount >= ind) {
		return keyOfOrder(ind, root->getLeft());
	}
	if (ind == leftcount + 1) {
		return root->getValue();
	}
	return keyOfOrder(ind - leftcount - 1, root->getRight());
}

int ImplicitTreap::maxDepth() const {
	return maxDepth(mRoot);
}

int ImplicitTreap::maxDepth(const ImplicitTreapNode* node) const {
	if (node == nullptr) {
		return 0;
	}
	return std::max(maxDepth(node->getRight()), maxDepth(node->getLeft())) + 1;
}

void ImplicitTreap::deallocate(ImplicitTreapNode* node) {
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