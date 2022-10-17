#pragma once
#include <utility>

class ImplicitTreapNode {
public:
	explicit ImplicitTreapNode(int v = 0, unsigned int p = 0, ImplicitTreapNode* lf = nullptr, ImplicitTreapNode* rg = nullptr)
		:mValue(v)
		, mPriority(p)
		, mLeft(lf)
		, mRight(rg)
		, mSize(1)
	{ update(); }
public:
	void setLeft(ImplicitTreapNode* node) {mLeft = node; update(); }
	void setRight(ImplicitTreapNode* node) {mRight = node; update(); }
	ImplicitTreapNode* getLeft() {return mLeft; }
	const ImplicitTreapNode* getLeft() const {return mLeft; }
	ImplicitTreapNode* getRight() {return mRight; }
	const ImplicitTreapNode* getRight() const {return mRight; }
	size_t size() const { return mSize; }
	size_t leftSize() const {return (mLeft != nullptr ? mLeft->mSize : 0); }
	size_t rightSize() const {return (mRight != nullptr ? mRight->mSize : 0); }
	const int& getValue() const {return mValue; }
public:
	static ImplicitTreapNode* merge(ImplicitTreapNode*, ImplicitTreapNode*);
	static std::pair<ImplicitTreapNode*, ImplicitTreapNode*> split(ImplicitTreapNode*, size_t);
private:
	void update() { mSize = leftSize() + rightSize() + 1; }
private:
	int mValue;
	unsigned int mPriority;
	ImplicitTreapNode* mLeft;
	ImplicitTreapNode* mRight;
	size_t mSize;
};


class ImplicitTreap {
public:
	ImplicitTreap();
	~ImplicitTreap();
	void pushBack(const int&);
	void insert(const int&, size_t);
	void remove(size_t);
    int maxDepth() const;
#ifdef TREAP_REVERSE
	void reverse(size_t, size_t);
#endif // TREAP_REVERSE
	int keyOfOrder(size_t) const;
	bool empty() const { return size() == 0; }
	size_t size() const { return mRoot != nullptr ? mRoot->size() : 0; }
private:
	void deallocate(ImplicitTreapNode*);
private:
	int keyOfOrder(size_t, ImplicitTreapNode*) const;
	int maxDepth(const ImplicitTreapNode*) const;
private:
	ImplicitTreapNode* mRoot;
};