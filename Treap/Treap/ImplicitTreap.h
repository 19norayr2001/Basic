#pragma once
#include <utility>

class ImplicitTreapNode {
public:
	ImplicitTreapNode(int v = 0, int p = 0, ImplicitTreapNode* lf = nullptr, ImplicitTreapNode* rg = nullptr)
		:mReverse(false)
		, mValue(v)
		, mPriority(p)
		, mLeft(lf)
		, mRight(rg)
		, mSize(1)
	{ update(); }
public:
	void changeLeft(ImplicitTreapNode* node) { updateParams(); mLeft = node; update(); }
	void changeRight(ImplicitTreapNode* node) { updateParams(); mRight = node; update(); }
	ImplicitTreapNode* getLeft() { updateParams(); return mLeft; }
	const ImplicitTreapNode* getLeft() const { updateParams(); return mLeft; }
	ImplicitTreapNode* getRight() { updateParams(); return mRight; }
	const ImplicitTreapNode* getRight() const { updateParams(); return mRight; }
	size_t size() const { return mSize; }
	size_t leftSize() const { updateParams(); return (mLeft != nullptr ? mLeft->mSize : 0); }
	size_t rightSize() const { updateParams(); return (mRight != nullptr ? mRight->mSize : 0); }
	const int& getValue() const { updateParams(); return mValue; }
	void reverse() { mReverse ^= true; }
public:
	static ImplicitTreapNode* merge(ImplicitTreapNode*, ImplicitTreapNode*);
	static std::pair<ImplicitTreapNode*, ImplicitTreapNode*> split(ImplicitTreapNode*, size_t);
private:
	void updateParams() const;
	void update() { mSize = leftSize() + rightSize() + 1; }
public:
	mutable bool mReverse;
private:
	int mValue;
	int mPriority;
	mutable ImplicitTreapNode* mLeft;
	mutable ImplicitTreapNode* mRight;
	size_t mSize;
};


class ImplicitTreap {
public:
	ImplicitTreap();
	~ImplicitTreap();
	void pushBack(const int&);
	void insert(const int&, size_t);
	void remove(size_t);
	void reverse(size_t, size_t);
	int keyOfOrder(size_t) const;
	int maxDepth() const;
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