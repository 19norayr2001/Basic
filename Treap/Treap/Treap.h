#pragma once
#include <utility>
class TreapNode
{
public:
	TreapNode(int k = 0, int p = 0, TreapNode* lf = nullptr, TreapNode* rg = nullptr)
		: key(k)
		, priority(p)
		, left(lf)
		, right(rg)
		, m_size(1)
	{ UpdateSize(); }
public:
	size_t size() const { return m_size; }
	size_t LeftSize() const { return (left != nullptr ? left->m_size : 0); }
	size_t RightSize() const { return (right != nullptr ? right->m_size : 0); }
public:
	static TreapNode* Merge(TreapNode*, TreapNode*);
	static std::pair<TreapNode*, TreapNode*> Split(TreapNode*, int);
private:
	void UpdateSize() { m_size = LeftSize() + RightSize() + 1; }
public:
	int key;
	TreapNode* left;
	TreapNode* right;
private:
	int priority;
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
	bool empty() const { return m_size == 0; }
	size_t size() const { return m_size; }
private:
	void Deallocate(TreapNode*);
private:
	bool Find(const int&, TreapNode*) const;
	int KeyOfOrder(size_t, TreapNode*) const;
	size_t OrderOfKey(const int&, TreapNode*) const;
	int MaxDepth(TreapNode*) const;
private:
	TreapNode* m_root;
	size_t m_size;
};