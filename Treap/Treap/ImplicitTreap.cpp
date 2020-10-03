#include "ImplicitTreap.h"
#include <algorithm>
#include <chrono>
#include <random>

ImplicitTreapNode* ImplicitTreapNode::Merge(ImplicitTreapNode* node1, ImplicitTreapNode* node2)
{
	if (node1 == nullptr)
		return node2;
	if (node2 == nullptr)
		return node1;
	ImplicitTreapNode* ret{};
	if (node1->m_priority > node2->m_priority)
	{
		ret = new ImplicitTreapNode(node1->Value(), node1->m_priority, node1->Left());
		ret->ChangeRight(Merge(node1->Right(), node2));
		delete node1;
	}
	else
	{
		ret = new ImplicitTreapNode(node2->Value(), node2->m_priority, nullptr, node2->Right());
		ret->ChangeLeft(Merge(node1, node2->Left()));
		delete node2;
	}
	return ret;
}

std::pair<ImplicitTreapNode*, ImplicitTreapNode*> ImplicitTreapNode::Split(ImplicitTreapNode* node, size_t x)
{
	if (node == nullptr || x <= 0)
		return std::make_pair(nullptr, node);
	if (x >= node->size())
		return std::make_pair(node, nullptr);
	ImplicitTreapNode* retleft{}, * retright{};
	if (node->LeftSize() < x)
	{
		std::pair<ImplicitTreapNode*, ImplicitTreapNode*> pright = ImplicitTreapNode::Split(node->Right(), x - node->LeftSize() - 1);
		retleft = node;
		node->ChangeRight(pright.first);
		retright = pright.second;
	}
	else
	{
		std::pair<ImplicitTreapNode*, ImplicitTreapNode*> pleft = ImplicitTreapNode::Split(node->Left(), x);
		retleft = pleft.first;
		retright = node;
		retright->ChangeLeft(pleft.second);
	}
	return std::make_pair(retleft, retright);
}

void ImplicitTreapNode::UpdateParams() const
{
	if (m_reverse)
	{
		std::swap(m_left, m_right);
		if (m_left != nullptr)
			m_left->Reverse();
		if (m_right != nullptr)
			m_right->Reverse();
		m_reverse = false;
	}
}

ImplicitTreap::ImplicitTreap()
	: m_root(nullptr)
{}

ImplicitTreap::~ImplicitTreap()
{
	Deallocate(m_root);
}

void ImplicitTreap::PushBack(const int& value)
{
	Insert(value, size());
}

void ImplicitTreap::Insert(const int& value, size_t ind)
{
	static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	ImplicitTreapNode* my_node = new ImplicitTreapNode(value, rng() % (1ll << 31));
	if (m_root == nullptr)
	{
		m_root = my_node;
		return;
	}
	std::pair<ImplicitTreapNode*, ImplicitTreapNode*> p = ImplicitTreapNode::Split(m_root, ind);
	m_root = ImplicitTreapNode::Merge(ImplicitTreapNode::Merge(p.first, my_node), p.second);
}

void ImplicitTreap::Delete(size_t ind)
{
	std::pair<ImplicitTreapNode*, ImplicitTreapNode*> first_split_pair = ImplicitTreapNode::Split(m_root, ind);
	std::pair<ImplicitTreapNode*, ImplicitTreapNode*> second_split_pair = ImplicitTreapNode::Split(first_split_pair.second, 1);
	if (second_split_pair.first == nullptr)
		throw std::exception("Element not found");
	delete second_split_pair.first;
	if (empty())
	{
		m_root = nullptr;
		return;
	}
	m_root = ImplicitTreapNode::Merge(first_split_pair.first, second_split_pair.second);
}

void ImplicitTreap::Reverse(size_t left, size_t right)
{
	if (left < 0)
		left = 0;
	if (right > size())
		right = size();
	if (right <= left)
		return;
	std::pair<ImplicitTreapNode*, ImplicitTreapNode*> p1 = ImplicitTreapNode::Split(m_root, left);
	std::pair<ImplicitTreapNode*, ImplicitTreapNode*> p2 = ImplicitTreapNode::Split(p1.second, right - left);
	p2.first->Reverse();
	m_root = ImplicitTreapNode::Merge(p1.first, ImplicitTreapNode::Merge(p2.first, p2.second));
}

int ImplicitTreap::KeyOfOrder(size_t ind) const
{
	if (ind >= size())
		throw std::exception("Index out of bounds");
	ind++;
	return KeyOfOrder(ind, m_root);
}

int ImplicitTreap::KeyOfOrder(size_t ind, ImplicitTreapNode* root) const
{
	size_t leftcount = root->LeftSize();
	if (leftcount >= ind)
		return KeyOfOrder(ind, root->Left());
	if (ind == leftcount + 1)
		return root->Value();
	return KeyOfOrder(ind - leftcount - 1, root->Right());
}

int ImplicitTreap::MaxDepth() const
{
	return MaxDepth(m_root);
}

int ImplicitTreap::MaxDepth(const ImplicitTreapNode* node) const
{
	if (node == nullptr)
		return 0;
	return std::max(MaxDepth(node->Right()), MaxDepth(node->Left())) + 1;
}

void ImplicitTreap::Deallocate(ImplicitTreapNode* node)
{
	if (node == nullptr)
		return;
	if (node->Left() != nullptr)
		Deallocate(node->Left());
	if (node->Right() != nullptr)
		Deallocate(node->Right());
	delete node;
}