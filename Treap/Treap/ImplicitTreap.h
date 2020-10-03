#pragma once
#include <utility>


class ImplicitTreapNode
{
public:
	ImplicitTreapNode(int v = 0, int p = 0, ImplicitTreapNode* lf = nullptr, ImplicitTreapNode* rg = nullptr)
		:m_reverse(false)
		, m_value(v)
		, m_priority(p)
		, m_left(lf)
		, m_right(rg)
		, m_size(1)
	{ Update(); }
public:
	void ChangeLeft(ImplicitTreapNode* node) { UpdateParams(); m_left = node; Update(); }
	void ChangeRight(ImplicitTreapNode* node) { UpdateParams(); m_right = node; Update(); }
	ImplicitTreapNode* Left() { UpdateParams(); return m_left; }
	const ImplicitTreapNode* Left() const { UpdateParams(); return m_left; }
	ImplicitTreapNode* Right() { UpdateParams(); return m_right; }
	const ImplicitTreapNode* Right() const { UpdateParams(); return m_right; }
	size_t size() const { return m_size; }
	size_t LeftSize() const { UpdateParams(); return (m_left != nullptr ? m_left->m_size : 0); }
	size_t RightSize() const { UpdateParams(); return (m_right != nullptr ? m_right->m_size : 0); }
	const int& Value() const { UpdateParams(); return m_value; }
	void Reverse() { m_reverse ^= true; }
public:
	static ImplicitTreapNode* Merge(ImplicitTreapNode*, ImplicitTreapNode*);
	static std::pair<ImplicitTreapNode*, ImplicitTreapNode*> Split(ImplicitTreapNode*, size_t);
private:
	void UpdateParams() const;
	void Update() { m_size = LeftSize() + RightSize() + 1; }
public:
	mutable bool m_reverse;
private:
	int m_value;
	int m_priority;
	mutable ImplicitTreapNode* m_left;
	mutable ImplicitTreapNode* m_right;
	size_t m_size;
};


class ImplicitTreap
{
public:
	ImplicitTreap();
	~ImplicitTreap();
	void PushBack(const int&);
	void Insert(const int&, size_t);
	void Delete(size_t);
	void Reverse(size_t, size_t);
	int KeyOfOrder(size_t) const;
	int MaxDepth() const;
	bool empty() const { return size() == 0; }
	size_t size() const { return m_root != nullptr ? m_root->size() : 0; }
private:
	void Deallocate(ImplicitTreapNode*);
private:
	int KeyOfOrder(size_t, ImplicitTreapNode*) const;
	int MaxDepth(const ImplicitTreapNode*) const;
private:
	ImplicitTreapNode* m_root;
};