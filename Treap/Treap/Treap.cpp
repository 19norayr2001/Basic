#include "Treap.h"
#include <algorithm>
#include <chrono>
#include <random>
TreapNode* TreapNode::Merge(TreapNode* node1, TreapNode* node2)
{
	if (node1 == nullptr)
		return node2;
	if (node2 == nullptr)
		return node1;
	if (node1->key > node2->key)
		std::swap(node1, node2);
	TreapNode* ret{};
	if (node1->priority > node2->priority)
	{
		ret = new TreapNode(node1->key, node1->priority, node1->left);
		ret->right = Merge(node1->right, node2);
		delete node1;
	}
	else
	{
		ret = new TreapNode(node2->key, node2->priority, nullptr, node2->right);
		ret->left = Merge(node2->left, node1);
		delete node2;
	}
	ret->UpdateSize();
	return ret;
}
std::pair<TreapNode*, TreapNode*> TreapNode::Split(TreapNode* node, int x)
{
	if (node == nullptr)
		return std::make_pair(nullptr, nullptr);
	TreapNode* retleft{}, * retright{};
	if (node->key < x)
	{
		std::pair<TreapNode*, TreapNode*> pright = TreapNode::Split(node->right, x);
		retleft = node;
		node->right = pright.first;
		retright = pright.second;
	}
	else
	{
		std::pair<TreapNode*, TreapNode*> pleft = TreapNode::Split(node->left, x);
		retleft = pleft.first;
		retright = node;
		retright->left = pleft.second;
	}
	if(retright != nullptr)
		retright->UpdateSize();
	if (retleft != nullptr)
		retleft->UpdateSize();
	return std::make_pair(retleft, retright);
}

Treap::Treap()
	: m_root(nullptr)
	, m_size(0)
{}

Treap::~Treap()
{
	Deallocate(m_root);
}

void Treap::Insert(const int& value)
{
	if (Find(value))
		return;
	static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	TreapNode* my_node = new TreapNode(value, rng() % (1ll << 31));
	m_size++;
	if (m_root == nullptr)
	{
		m_root = my_node;
		return;
	}
	std::pair<TreapNode*, TreapNode*> p = TreapNode::Split(m_root, value);
	m_root = TreapNode::Merge(p.second, TreapNode::Merge(p.first, my_node));
}

void Treap::Delete(const int& value)
{
	std::pair<TreapNode*, TreapNode*> first_split_pair = TreapNode::Split(m_root, value);
	std::pair<TreapNode*, TreapNode*> second_split_pair = TreapNode::Split(first_split_pair.second, value + 1);
	if (second_split_pair.first == nullptr)
		throw std::exception("Element not found");
	m_size--;
	delete second_split_pair.first;
	if (m_size == 0)
	{
		m_root = nullptr;
		return;
	}
	m_root = TreapNode::Merge(first_split_pair.first, second_split_pair.second);
}

bool Treap::Find(const int& value) const
{
	return Find(value, m_root);
}

bool Treap::Find(const int& value, TreapNode* root) const
{
	if (root == nullptr)
		return false;
	if (value == root->key)
		return true;
	if (value < root->key)
		return Find(value, root->left);
	return Find(value, root->right);
}

int Treap::KeyOfOrder(size_t ind) const
{
	if (ind >= m_size)
		throw std::exception("Index out of bounds");
	ind++;
	return KeyOfOrder(ind, m_root);
}

int Treap::KeyOfOrder(size_t ind, TreapNode* root) const
{
	size_t leftcount = (root->left != nullptr ? root->left->size() : 0);
	if (leftcount >= ind)
		return KeyOfOrder(ind, root->left);
	if (ind == leftcount + 1)
		return root->key;
	return KeyOfOrder(ind - leftcount - 1, root->right);
}

size_t Treap::OrderOfKey(const int& key) const
{
	return OrderOfKey(key, m_root) - 1;
}

size_t Treap::OrderOfKey(const int& key, TreapNode* root) const
{
	if (root == nullptr)
		throw std::exception("Element not found");
	if (key == root->key)
		return 1 + root->LeftSize();
	if (key < root->key)
		return OrderOfKey(key, root->left);
	return 1 + root->LeftSize() + OrderOfKey(key, root->right);
}

int Treap::MaxDepth() const
{
	return MaxDepth(m_root);
}

int Treap::MaxDepth(TreapNode* node) const
{
	if (node == nullptr)
		return 0;
	return std::max(MaxDepth(node->right), MaxDepth(node->left)) + 1;
}

void Treap::Deallocate(TreapNode* node)
{
	if (node == nullptr)
		return;
	if (node->left != nullptr)
		Deallocate(node->left);
	if (node->right != nullptr)
		Deallocate(node->right);
	delete node;
}