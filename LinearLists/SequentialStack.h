#pragma once
#include <iostream>
class SequentialStack
{
public:
	SequentialStack();
	SequentialStack(const SequentialStack&);
	SequentialStack& operator=(const SequentialStack&);
	~SequentialStack();
public:
	bool empty() const { return m_size == 0; }
	int size() const { return m_size; }
	const int& top() const;
	int& top();
	void push(const int&);
	void pop();
	friend std::ostream& operator<<(std::ostream&, SequentialStack&);

private:
	int m_size;
	int m_maxsize;
	int* m_array;
};

