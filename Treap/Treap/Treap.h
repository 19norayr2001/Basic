#pragma once
class TreapNode
{
public:
	TreapNode(int k = 0, int p = 0, TreapNode* lf = nullptr, TreapNode* rg = nullptr)
		: key(k)
		, priority(p)
		, left(lf)
		, right(rg)
	{}
	int key;
	int priority;
	TreapNode* left;
	TreapNode* right;
};
class Treap
{
public:
	Treap();
	void Insert(const int&);
	void Delete(const int&);
	bool Find(const int&) const;
	bool empty() const { return m_size == 0; }
	size_t size() const { return m_size; }
private:
	bool Find(const int&, TreapNode*) const;
private:
	TreapNode* m_root;
	size_t m_size;
};

