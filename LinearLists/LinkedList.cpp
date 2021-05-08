#include <iostream>

#include "LinkedList.h"

LinkedList::LinkedList()
	: m_head(nullptr)
	, m_tail(nullptr)
{
	m_head = m_tail = new Node();
	m_head->next = m_head;
	m_head->previous = m_head;
}

LinkedList::LinkedList(const LinkedList& object)
{
	allocate(object);
}

LinkedList& LinkedList::operator=(const LinkedList& object)
{
	if (this != &object)
	{
		deallocate();
		allocate(object);
	}
	return *this;
}

LinkedList::~LinkedList()
{
	deallocate();
}

void LinkedList::push_back(const int& num)
{
	m_tail->next = new Node(num);
	m_tail->next->previous = m_tail;
	m_tail = m_tail->next;
	m_tail->next = m_head;
}

void LinkedList::pop_back()
{
	if (m_head != m_tail)
	{
		m_tail = m_tail->previous;
		delete m_tail->next;
		m_tail->next = m_head;
	}
}

void LinkedList::push_front(const int& num)
{
	m_head->value = num;
	m_head->previous = new Node();
	m_head->previous->next = m_head;
	m_head = m_head->previous;
	m_head->previous = m_tail;
	m_tail->next = m_head;
}

void LinkedList::pop_front()
{
	if (m_head != m_tail)
	{
		m_head = m_head->next;
		delete m_head->previous;
		m_head->previous = m_tail;
		m_tail->next = m_head;
	}
}

void LinkedList::insert(const int& value, Node* prev)
{
	if (prev == m_tail)
	{
		this->push_back(value);
	}
	else
	{
		Node* temp = new Node(value);
		temp->previous = prev;
		temp->next = prev->next;
		prev->next = temp;
		temp->next->previous = temp;
	}
}

void LinkedList::erase(Node* obj)
{
	if (obj == m_tail)
	{
		this->pop_back();
	}
	else
	{
		obj->previous->next = obj->next;
		obj->next->previous = obj->previous;
		delete obj;
	}
}

std::ostream& operator<<(std::ostream& print, LinkedList& obj)
{
	LinkedList::Node* ptr = obj.m_head->next;
	while (ptr != obj.m_head)
	{
		print << ptr->value << std::endl;
		ptr = ptr->next;
	}
	return print;
}

void LinkedList::allocate(const LinkedList& object)
{
	Node* ptrobj = object.m_head;
	m_head = new Node();
	Node* ptrthis = m_head;
	while (ptrobj->next != object.m_head)
	{
		ptrthis->next = new Node();
		ptrthis->next->previous = ptrthis;
		ptrthis->next->value = ptrobj->next->value;
		ptrthis = ptrthis->next;
		ptrobj = ptrobj->next;
	}
	m_tail = ptrthis;
	m_tail->next = m_head;
	m_head->previous = m_tail;
}

void LinkedList::deallocate()
{
	Node* ptr = m_head;
	while (ptr != m_tail)
	{
		ptr = ptr->next;
		delete ptr->previous;
	}
	delete m_tail;
}