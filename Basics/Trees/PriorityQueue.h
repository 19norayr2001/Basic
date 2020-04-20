#pragma once
#include "../LinearLists/SequentialList.h"

class PriorityQueue
{
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue&);
	PriorityQueue& operator=(const PriorityQueue&);
	~PriorityQueue();
public:
	const int& top() const;
	void insert(const int&);
	void pop();
private:
	void allocate(const PriorityQueue&);
	void deallocate();
private:
	SequentialList m_heap;
	int m_size;
};