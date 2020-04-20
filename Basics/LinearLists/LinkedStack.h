#pragma once
#include <iostream>
class LinkedStack
{
public:
	struct Node
	{
		int value;
		Node* previous;
		Node(int v = 0)
			:value(v)
			, previous(nullptr)
		{}
	};
	LinkedStack();
	LinkedStack(const LinkedStack&);
	LinkedStack& operator=(const LinkedStack&);
	~LinkedStack();
public:
	bool empty() const { return m_size == 0; }
	int size() const { return m_size; }
	const int& top() const;
	int& top();
	void push(const int&);
	void pop();
	friend std::ostream& operator<<(std::ostream&, LinkedStack&);
private:
	void allocate(const LinkedStack&);
	void deallocate();
private:
	Node* m_top;
	int m_size;
};

