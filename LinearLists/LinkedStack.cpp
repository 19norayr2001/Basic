#include "LinkedStack.h"

LinkedStack::LinkedStack()
	:m_top(nullptr)
	, m_size(0)
{}

LinkedStack::LinkedStack(const LinkedStack& object)
{
	allocate(object);
}

LinkedStack& LinkedStack::operator=(const LinkedStack& object)
{
	if (this != &object)
	{
		deallocate();
		allocate(object);
	}
	return *this;
}

LinkedStack::~LinkedStack()
{
	deallocate();
}

const int& LinkedStack::top() const
{
	return m_top->value;
}

int& LinkedStack::top()
{
	return m_top->value;
}

void LinkedStack::push(const int& val)
{
	Node* ptr = new Node(val);
	ptr->previous = m_top;
	m_top = ptr;
	m_size++;
}

void LinkedStack::pop()
{
	if (m_top != nullptr)
	{
		m_size--;
		Node* ptr = m_top;
		m_top = m_top->previous;
		delete ptr;
	}
}

std::ostream& operator<<(std::ostream& print, LinkedStack& object)
{
	LinkedStack::Node* ptr = object.m_top;
	while (ptr != nullptr)
	{
		print << ptr->value << " ";
		ptr = ptr->previous;
	}
	return print;
}

void LinkedStack::allocate(const LinkedStack& object)
{
	m_size = object.m_size;
	if (object.empty())
	{
		m_top = nullptr;
		return;
	}
	Node* ptr = object.m_top;
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
			m_top = prev;
		}
		next = prev;
	}
}

void LinkedStack::deallocate()
{
	while (m_top != nullptr)
	{
		Node* temp = m_top;
		m_top = m_top->previous;
		delete temp;
	}
}