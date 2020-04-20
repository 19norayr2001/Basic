#include "LinkedQueue.h"

LinkedQueue::LinkedQueue()
	:m_front(nullptr)
	, m_end(nullptr)
	, m_size(0)
{}

LinkedQueue::LinkedQueue(const LinkedQueue& object)
{
	allocate(object);
}

LinkedQueue& LinkedQueue::operator=(const LinkedQueue& object)
{
	if (this != &object)
	{
		deallocate();
		allocate(object);
	}
	return *this;
}

LinkedQueue::~LinkedQueue()
{
	deallocate();
}

const int& LinkedQueue::front() const
{
	return m_front->value;
}

int& LinkedQueue::front()
{
	return m_front->value;
}

void LinkedQueue::push(const int& val)
{
	if (m_end != nullptr)
	{
		m_end->previous = new Node(val);
		m_end = m_end->previous;
	}
	else
	{
		m_front = m_end = new Node(val);
	}
	m_size++;
}

void LinkedQueue::pop()
{
	if (m_front != nullptr)
	{
		Node* ptr = m_front;
		m_front = m_front->previous;
		delete ptr;
		if (m_front == nullptr)
		{
			m_end = nullptr;
		}
		m_size--;
	}
}

std::ostream& operator<<(std::ostream& print, LinkedQueue& object)
{
	LinkedQueue::Node* ptr = object.m_front;
	while (ptr != nullptr)
	{
		print << ptr->value;
		ptr = ptr->previous;
	}
	return print;
}

void LinkedQueue::allocate(const LinkedQueue& object)
{
	m_size = object.m_size;
	if (object.empty())
	{
		m_front = m_end = nullptr;
		return;
	}
	Node* ptr = object.m_front;
	Node* next = nullptr;
	while (ptr != nullptr)
	{
		Node* prev = new Node(ptr->value);
		ptr = ptr->previous;
		if (next != nullptr)
		{
			next->previous = prev;
		}
		else
		{
			m_front = prev;
		}
		next = prev;
	}
	m_end = next;
}

void LinkedQueue::deallocate()
{
	while (m_front != nullptr)
	{
		Node* temp = m_front;
		m_front = m_front->previous;
		delete temp;
	}
}