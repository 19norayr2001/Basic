#include "Treap.h"
#include <algorithm>
#include <chrono>
#include <random>
namespace
{
	TreapNode* Merge(TreapNode* node1, TreapNode* node2)
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
		return ret;
	}
	std::pair<TreapNode*, TreapNode*> Split(TreapNode* node, int x)
	{
		if (node == nullptr)
			return std::make_pair(nullptr, nullptr);
		TreapNode* retleft{}, * retright{};
		if (node->key < x)
		{
			std::pair<TreapNode*, TreapNode*> pright = Split(node->right, x);
			retleft = node;
			node->right = pright.first;
			retright = pright.second;
		}
		else
		{
			std::pair<TreapNode*, TreapNode*> pleft = Split(node->left, x);
			retleft = pleft.first;
			retright = node;
			retright->left = pleft.second;
		}
		return std::make_pair(retleft, retright);
	}

	void RemoveTree(TreapNode* node)
	{
		if (node == nullptr)
			return;
		if (node->left != nullptr)
			RemoveTree(node->left);
		if (node->right != nullptr)
			RemoveTree(node->right);
		delete node;
	}
}

Treap::Treap()
	:m_root(nullptr)
{}
void Treap::Insert(const int& value)
{
	static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	TreapNode* my_node = new TreapNode(value, rng()%(1ll<<31));
	if (m_root == nullptr)
	{
		m_root = my_node;
		return;
	}
	std::pair<TreapNode*, TreapNode*> p = Split(m_root, value);
	m_root = Merge(p.second, Merge(p.first, my_node));
}

void Treap::Delete(const int& value)
{
	std::pair<TreapNode*, TreapNode*> first_split_pair = Split(m_root, value);
	std::pair<TreapNode*, TreapNode*> second_split_pair = Split(first_split_pair.second, value + 1);
	if (second_split_pair.first == nullptr)
	{
		return;
	}
	RemoveTree(second_split_pair.first);
	m_root = Merge(first_split_pair.first, second_split_pair.second);
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