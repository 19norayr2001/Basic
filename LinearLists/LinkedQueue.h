#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <iostream>
class LinkedQueue
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
	LinkedQueue();
	LinkedQueue(const LinkedQueue&);
	LinkedQueue& operator=(const LinkedQueue&);
	~LinkedQueue();
public:
	bool empty() const { return m_size == 0; }
	int size() const { return m_size; }
	const int& front() const;
	int& front();
	void push(const int&);
	void pop();
	friend std::ostream& operator<<(std::ostream&, LinkedQueue&);
private:
	void allocate(const LinkedQueue&);
	void deallocate();
private:
	Node* m_front;
	Node* m_end;
	int m_size;
};

#endif // LINKED_QUEUE_H