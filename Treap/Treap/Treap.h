#pragma once
#include <utility>

class TreapNode
{
public:
	TreapNode(int k = 0, int p = 0, TreapNode* lf = nullptr, TreapNode* rg = nullptr)
		: key(k)
		, priority(p)
		, m_left(lf)
		, m_right(rg)
		, m_size(1)
	{ Update(); }
public:
	void ChangeLeft(TreapNode* node) { Update(); m_left = node; }
	void ChangeRight(TreapNode* node) { Update(); m_right = node; }
	TreapNode* Left() { return m_left; }
	const TreapNode* Left() const { return m_left; }
	TreapNode* Right() { return m_right; }
	const TreapNode* Right() const { return m_right; }
	size_t size() const { return m_size; }
	size_t LeftSize() const { return (m_left != nullptr ? m_left->m_size : 0); }
	size_t RightSize() const { return (m_right != nullptr ? m_right->m_size : 0); }
public:
	static TreapNode* Merge(TreapNode*, TreapNode*);
	static std::pair<TreapNode*, TreapNode*> Split(TreapNode*, int);
private:
	void Update() { m_size = LeftSize() + RightSize() + 1; }
public:
	int key;
private:
	int priority;
	TreapNode* m_left;
	TreapNode* m_right;
	size_t m_size;
};

class Treap
{
public:
	Treap();
	~Treap();
	void Insert(const int&);
	void Delete(const int&);
	bool Find(const int&) const;
	int KeyOfOrder(size_t) const;
	size_t OrderOfKey(const int&) const;
	int MaxDepth() const;
	bool empty() const { return size() == 0; }
	size_t size() const { return m_root != nullptr ? m_root->size() : 0; }
private:
	void Deallocate(TreapNode*);
private:
	bool Find(const int&, TreapNode*) const;
	int KeyOfOrder(size_t, const TreapNode*) const;
	size_t OrderOfKey(const int&, const TreapNode*) const;
	int MaxDepth(const TreapNode*) const;
private:
	TreapNode* m_root;
};