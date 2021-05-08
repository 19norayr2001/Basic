#pragma once
#include <vector>

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
	std::vector<int> m_heap;
	int m_size;
};