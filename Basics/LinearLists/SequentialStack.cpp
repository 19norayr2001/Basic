#include "SequentialStack.h"

static const int MAXSIZE = 100;

SequentialStack::SequentialStack()
	: m_size(0)
	, m_maxsize(MAXSIZE)
	, m_array(nullptr)
{
	m_array = new int[m_maxsize];
}

SequentialStack::SequentialStack(const SequentialStack& object)
	: m_size(object.m_size)
	, m_maxsize(object.m_maxsize)
	, m_array(nullptr)
{
	m_array = new int[m_maxsize];
	for (int i = 0; i < m_size; ++i) {
		m_array[i] = object.m_array[i];
	}
}

SequentialStack& SequentialStack::operator=(const SequentialStack& object)
{
	if (this != &object)
	{
		delete[] m_array;
		m_size = object.m_size;
		m_maxsize = object.m_maxsize;
		m_array = new int[m_maxsize];
		for (int i = 0; i < m_size; ++i) {
			m_array[i] = object.m_array[i];
		}
	}
	return *this;
}

SequentialStack::~SequentialStack()
{
	delete[] m_array;
}

int& SequentialStack::top()
{
	return m_array[m_size - 1];
}

const int& SequentialStack::top() const
{
	return m_array[m_size - 1];
}

void SequentialStack::push(const int& number)
{
	if (m_size == m_maxsize) {
		m_maxsize *= 2;
		int *p = new int[m_maxsize];
		for (int i = 0; i < m_size; ++i)
			p[i] = m_array[i];
		delete[]m_array;
		m_array = p;
	}
	m_array[m_size] = number;
	m_size++;
}

void SequentialStack::pop()
{
	if (m_size > 0)
		m_size--;
}


std::ostream& operator<<(std::ostream& print, SequentialStack& obj)
{
	for (int i = obj.m_size - 1; i >= 0; --i)
	{
		std::cout << obj.m_array[i] << " ";
	}
	std::cout << std::endl;
	return print;
}