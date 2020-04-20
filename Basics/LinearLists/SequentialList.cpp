#include "SequentialList.h"

static const int MAX_SIZE = 100;

SequentialList::SequentialList()
	: m_maxsize(MAX_SIZE)
	, m_size(0)
	, m_array(nullptr)
{
	m_array = new int[m_maxsize];	
}

SequentialList::SequentialList(const SequentialList& object)
	: m_maxsize(object.m_maxsize)
	, m_size(object.m_size)
	, m_array(nullptr) 
{
	m_array = new int[m_maxsize];
	for (int i = 0; i < m_size; ++i) {
		m_array[i] = object.m_array[i];
	}
}

SequentialList& SequentialList::operator=(const SequentialList& object)
{
	if (this != &object) {
		delete[] m_array;
		m_size = object.m_size;
		m_maxsize = object.m_maxsize;
		m_array = new int[m_maxsize];
		for (int i = 0; i < m_size; ++i) {
			m_array[i] = object[i];
		}
	}
	return *this;
}

SequentialList::~SequentialList()
{
	delete[] m_array;
}

void SequentialList::push_back(const int& num)
{
	if (m_size == m_maxsize) {
		m_maxsize *= 2;
		int* p = new int[m_maxsize];
		for (int i = 0; i < m_size; ++i)
			p[i] = m_array[i];
		delete[] m_array;
		m_array = p;
	}
	m_array[m_size++] = num;
}

void SequentialList::pop_back()
{
	if (!is_empty()) {
		--m_size;
	}
}
void SequentialList::insert(int ind, const int& num)
{
	if (m_size == m_maxsize)
	{
		m_maxsize *= 2;
		int* p = new int[m_maxsize];
		for (int i = 0; i < ind; ++i) {
			p[i] = m_array[i];
		}
		p[ind] = num;
		for (int i = ind + 1; i <= m_size; ++i){
			p[i] = m_array[i - 1];
		}
		m_size++;
		delete[] m_array;
		m_array = p;
	}
	else
	{
		int temp = num;
		m_size++;
		for (int i = ind; i < m_size; ++i) {
			std::swap(m_array[i], temp);
		}
	}
}

void SequentialList::remove(int ind)
{
	m_size--;
	for (int i = ind; i < m_size; ++i) {
		m_array[i] = m_array[i + 1];
	}
}

int& SequentialList::operator[](int ind)
{
	return m_array[ind];
}

const int& SequentialList::operator[](int ind) const
{
	return m_array[ind];
}

std::ostream& operator<<(std::ostream& print, SequentialList& obj)
{
	for (int i = 0; i < obj.m_size; ++i)
	{
		std::cout << obj.m_array[i] << " ";
	}
	std::cout << std::endl;
	return print;
}