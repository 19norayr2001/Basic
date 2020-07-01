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
		ret = new TreapNode(node1->key, node1->priority, node1->Left());
		ret->ChangeRight(Merge(node1->Right(), node2));
		delete node1;
	}
	else
	{
		ret = new TreapNode(node2->key, node2->priority, nullptr, node2->Right());
		ret->ChangeLeft(Merge(node1, node2->Left()));
		delete node2;
	}
	return ret;
}

std::pair<TreapNode*, TreapNode*> TreapNode::Split(TreapNode* node, int x)
{
	if (node == nullptr)
		return std::make_pair(nullptr, nullptr);
	TreapNode* retleft{}, * retright{};
	if (node->key < x)
	{
		std::pair<TreapNode*, TreapNode*> pright = TreapNode::Split(node->Right(), x);
		retleft = node;
		node->ChangeRight(pright.first);
		retright = pright.second;
	}
	else
	{
		std::pair<TreapNode*, TreapNode*> pleft = TreapNode::Split(node->Left(), x);
		retleft = pleft.first;
		retright = node;
		retright->ChangeLeft(pleft.second);
	}
	return std::make_pair(retleft, retright);
}

Treap::Treap()
	: m_root(nullptr)
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
	delete second_split_pair.first;
	if (empty())
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
		return Find(value, root->Left());
	return Find(value, root->Right());
}

int Treap::KeyOfOrder(size_t ind) const
{
	if (ind >= size())
		throw std::exception("Index out of bounds");
	ind++;
	return KeyOfOrder(ind, m_root);
}

int Treap::KeyOfOrder(size_t ind, const TreapNode* root) const
{
	size_t leftcount = root->LeftSize();
	if (leftcount >= ind)
		return KeyOfOrder(ind, root->Left());
	if (ind == leftcount + 1)
		return root->key;
	return KeyOfOrder(ind - leftcount - 1, root->Right());
}

size_t Treap::OrderOfKey(const int& key) const
{
	return OrderOfKey(key, m_root) - 1;
}

size_t Treap::OrderOfKey(const int& key, const TreapNode* root) const
{
	if (root == nullptr)
		throw std::exception("Element not found");
	if (key == root->key)
		return 1 + root->LeftSize();
	if (key < root->key)
		return OrderOfKey(key, root->Left());
	return 1 + root->LeftSize() + OrderOfKey(key, root->Right());
}

int Treap::MaxDepth() const
{
	return MaxDepth(m_root);
}

int Treap::MaxDepth(const TreapNode* node) const
{
	if (node == nullptr)
		return 0;
	return std::max(MaxDepth(node->Right()), MaxDepth(node->Left())) + 1;
}

void Treap::Deallocate(TreapNode* node)
{
	if (node == nullptr)
		return;
	if (node->Left() != nullptr)
		Deallocate(node->Left());
	if (node->Right() != nullptr)
		Deallocate(node->Right());
	delete node;
}